#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>
#include <stdexcept>

// Header only helpers for frozen encoder
#include "metkit/mars2grib/backend/sections/sections-recipes.h"
#include "metkit/mars2grib/backend/concepts/concept-registry.h"

namespace metkit {
namespace mars2grib {
namespace backend {

// ============================================================
// External hooks to be provided by you (domain logic)
// ============================================================

// 1) Read template numbers for the 5 sections from cfg
template<class Cfg_t>
std::array<uint16_t, 5> read_template_numbers(const Cfg_t& cfg);

// 2) Read concept type from cfg for given concept name
template<class Cfg_t>
std::string_view read_concept_type(const Cfg_t& cfg,
                                   std::string_view conceptName);

// 3) Given (name,type) return the 3×NSECTIONS table of Fn_t
template<class Fn_t, std::size_t NSECTIONS, std::size_t NSTAGES>
using ConceptFnTable = std::array<std::array<Fn_t, NSECTIONS>, NSTAGES>;

template<class Fn_t, std::size_t NSECTIONS, std::size_t NSTAGES>
ConceptFnTable<Fn_t, NSECTIONS, NSTAGES>
lookup_concept_fn_table(std::string_view name,
                        std::string_view type);

// 4) Section initializer selection: per section and template number
template<class OUT>
using IFn_t = void(*)(OUT&);

template<std::size_t SectionIdx, class OutDict_t, class Cfg_t>
IFn_t<OutDict_t>
select_section_initializer(uint16_t templateNumber,
                           const Cfg_t& cfg);



// ============================================================
// Free functions used by FrozenEncoder (make_*)
// ============================================================

//
// template numbers
template<
    std::size_t NSECTIONS,
    std::size_t NSTAGES,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t,
    class Cfg_t
>
inline std::array<uint16_t, NSECTIONS>
make_template_numbers(const Cfg_t& cfg)
{
    static_assert(NSECTIONS == 5, "Assumes 5 sections.");
    return read_template_numbers(cfg); // your implementation
}



//
// section initializers
template<
    std::size_t NSECTIONS,
    std::size_t NSTAGES,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t,
    class Cfg_t
>
inline std::array<std::pair<uint16_t, IFn_t<OutDict_t>>, NSECTIONS>
make_section_initializers(const Cfg_t& cfg,
                          const std::array<uint16_t, NSECTIONS>& tmplNumbers)
{
    std::array<std::pair<uint16_t, IFn_t<OutDict_t>>, NSECTIONS> inits{};

    for (std::size_t secIdx = 0; secIdx < NSECTIONS; ++secIdx) {
        const uint16_t tmpl = tmplNumbers[secIdx];
        IFn_t<OutDict_t> fn = nullptr;

        switch (secIdx) {
            case 0:
                fn = select_section_initializer<0, OutDict_t>(tmpl, cfg);
                break;
            case 1:
                fn = select_section_initializer<1, OutDict_t>(tmpl, cfg);
                break;
            case 2:
                fn = select_section_initializer<2, OutDict_t>(tmpl, cfg);
                break;
            case 3:
                fn = select_section_initializer<3, OutDict_t>(tmpl, cfg);
                break;
            case 4:
                fn = select_section_initializer<4, OutDict_t>(tmpl, cfg);
                break;
            default:
                break;
        }

        inits[secIdx] = std::make_pair(tmpl, fn);
    }

    return inits;
}

//
// callbacks
template<
    std::size_t NSECTIONS,
    std::size_t NSTAGES,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t,
    class Cfg_t
>
inline typename FrozenEncoder<NSECTIONS, NSTAGES,
                              MarsDict_t, GeoDict_t,
                              ParDict_t, OptDict_t,
                              OutDict_t, Cfg_t>::Callbacks
make_callbacks(const Cfg_t& cfg,
               const std::array<uint16_t, NSECTIONS>& tmplNumbers)
{
    using Encoder = FrozenEncoder<NSECTIONS, NSTAGES,
                                  MarsDict_t, GeoDict_t,
                                  ParDict_t, OptDict_t,
                                  OutDict_t, Cfg_t>;
    using Fn_t = typename Encoder::Fn_t;
    using Callbacks = typename Encoder::Callbacks;

    Callbacks cb; // empty vectors

    // For each section, locate recipe and process all concepts
    for (std::size_t secIdx = 0; secIdx < NSECTIONS; ++secIdx) {

        // Get template number of the current section
        const uint16_t tmpl = tmplNumbers[secIdx];

        // From recipe get the list of concepts
        const std::optional<ConceptList> recipe =
                            searchConceptsInSection(secIdx, tmpl);
        if (!recipe) {
            throw std::runtime_error("Missing recipe for section/template");
        }

        for (const auto& cs : *recipe) {

            // Convert concept name to string_view
            const std::string_view conceptName = cs.name;
            const std::string_view cfgType =
                read_concept_type(cfg, conceptName);

            // Convert effective type to string_view
            std::string_view effectiveType = cfgType;

            // If the recipe specifies a type, it must match cfg type
            if (cs.type.has_value()) {
                if (cfgType != *cs.type) {
                    throw std::runtime_error("Concept type mismatch");
                }
                effectiveType = *cs.type;
            }

            // (name, effectiveType) → 3×NSECTIONS table of Fn_t
            auto fnTable = registry.map[{conceptName,effectiveType}];

            // Append functions to callbacks if relevant
            for (std::size_t stage = 0; stage < NSTAGES; ++stage) {
                for (std::size_t s = 0; s < NSECTIONS; ++s) {
                    Fn_t f = fnTable[stage][s];
                    if (f) {
                        cb[stage][s].push_back(f);
                    }
                }
            }
        }
    }

    return cb;
}



// ============================================================
// FrozenEncoder (all immutable)
// ============================================================

template<
    uint8_t NSECTIONS,
    uint8_t NSTAGES,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t,
    class Cfg_t
>
class FrozenEncoder
{
public:
    // Base function pointer type
    template<class MD, class GD, class PD, class ODp, class OUT>
    using Fn = uint8_t(*)(const MD&, const GD&, const PD&, const ODp&, OUT&);

    using Fn_t = Fn<MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t>;

    using Callbacks = std::array<
        std::array<std::vector<Fn_t>, NSECTIONS>,  // sections
        NSTAGES                                    // stages
    >;

    using TemplateNumbers   = std::array<uint16_t, NSECTIONS>;
    using SectionInitFn     = IFn_t<OutDict_t>;
    using SectionInitializers =
        std::array<std::pair<uint16_t, SectionInitFn>, NSECTIONS>;

    static_assert(NSECTIONS == 5, "Current design assumes 5 sections.");

public:
    explicit FrozenEncoder(const Cfg_t& cfg)
        : templateNumbers_(make_template_numbers(cfg))
        , callbacks_(make_callbacks(cfg, templateNumbers_))
        , sectionInits_(make_section_initializers(cfg, templateNumbers_))
    {}

    const TemplateNumbers& template_numbers() const noexcept {
        return templateNumbers_;
    }

    const Callbacks& callbacks() const noexcept {
        return callbacks_;
    }

    const SectionInitializers& section_initializers() const noexcept {
        return sectionInits_;
    }

    // Encode a single stage I over all sections and their callbacks
    template<std::size_t I,
             class MD, class GD, class PD, class ODp, class OUT>
    void encode(const MD& md,
                const GD& gd,
                const PD& pd,
                const ODp& odp,
                OUT& out) const
    {
        static_assert(I < NSTAGES, "Stage index out of range");

        const auto& stageVecs = callbacks_[I];

        for (std::size_t secIdx = 0; secIdx < NSECTIONS; ++secIdx) {
            const auto& fns = stageVecs[secIdx];
            for (Fn_t fn : fns) {
                fn(md, gd, pd, odp, out);
            }
        }
    }

    // Encode all stages, all sections
    template<class MD, class GD, class PD, class ODp, class OUT>
    void encode(const MD& md,
                const GD& gd,
                const PD& pd,
                const ODp& odp,
                OUT& out) const
    {
        for (std::size_t stage = 0; stage < NSTAGES; ++stage) {
            const auto& stageVecs = callbacks_[stage];
            for (std::size_t secIdx = 0; secIdx < NSECTIONS; ++secIdx) {
                const auto& fns = stageVecs[secIdx];
                for (Fn_t fn : fns) {
                    fn(md, gd, pd, odp, out);
                }
            }
        }
    }

private:
    const TemplateNumbers    templateNumbers_;
    const Callbacks          callbacks_;
    const SectionInitializers sectionInits_;

}; // class FrozenEncoder

}
}
}