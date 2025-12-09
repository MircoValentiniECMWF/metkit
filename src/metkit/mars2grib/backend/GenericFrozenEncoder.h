#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>
#include <stdexcept>

// Header only helpers for frozen encoder
#include "metkit/mars2grib/backend/sections/sections_recipes.h"
#include "metkit/mars2grib/backend/concepts/concept_registry.h"
#include "metkit/mars2grib/utils/encoder_cfg.h"

namespace metkit::mars2grib::backend {



// Get the callbacks table
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
inline std::array<std::array<std::vector<Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>>, NUM_SECTIONS>, NUM_STAGES>
make_callbacks( std::array<std::vector<std::pair<std::string_view,std::string_view>>, NUM_SECTIONS> conceptsArr )
{

    // Get the concept registry instance
    const auto& registry = concept_registry_instance<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>();

    // Prepare callback table
    std::array<std::array<std::vector<Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>>, NUM_SECTIONS>, NUM_STAGES> table{};

    // Populate callback table
    for ( uint16_t sid=0; sid<NUM_SECTIONS; ++sid ) {
      for ( const auto& cs : conceptsArr[sid] ) {

          auto it = registry.map.find(cs);
          if ( it == registry.map.end()) {
              std::cout << "ERROR: Concept not found: " << cs.first << " / " << cs.second << std::endl;
              throw std::runtime_error("Concept not found in registry");
          }
          auto fnTable = it->second;

          // Append functions to callbacks if relevant
          for (std::size_t stage = 0; stage < NUM_STAGES; ++stage) {
              auto f = fnTable[stage][sid];
              std::cout << "Register Callbacks :: Stage: " << stage << ", Section: " << sid << ", isValid: " << (f ? "true" : "false") << std::endl;
              if (f) {
                  table[stage][sid].push_back(f);
              }
          }
      }
    }

    return table;
};

// This is an generic encoder fully templated on all the dictionaries
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
class GenericFrozenEncoder
{
public:

    // Definition of a callback
    using Fn_t = Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>;

    // Definition of callbacks container
    using Callbacks = std::array<
        std::array<std::vector<Fn_t>, NUM_SECTIONS>,  // sections
        NUM_STAGES                                    // stages
    >;

public:

    explicit GenericFrozenEncoder(const utils::EncoderCfg& cfg)
        : cfg_{cfg},callbacks_{make_callbacks<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(
              make_section_concepts(cfg))}
    {}

    void debug_print() const {

      std::cout << "========================================================" << std::endl;
      int secId =0;
      for ( const auto& sec : cfg_.sec_ ) {
          std::cout << "Section " << secId << "." << sec.templateNumber_ << ":" << std::endl;
          for ( const auto& concept : sec.concepts_ ) {
              std::cout << "Section " << secId << "." << sec.templateNumber_ <<
              ": Concept " << concept.first << " / " << concept.second << std::endl;
          }
          ++secId;
      }
      std::cout << "========================================================" << std::endl;

      // Generate the expanded configuration in order to debug concept expansion
      const auto& expanded_configuration = make_section_concepts(cfg_);

      // print expanded configuration
      for ( uint16_t sid=0; sid<NUM_SECTIONS; ++sid ) {
        std::cout << " + Section " << sid << std::endl;
        for ( const auto& cs : expanded_configuration[sid] ) {

            std::cout << "     - Concept processed: " << cs.first << " / " << cs.second << std::endl;

        }
      }

    };

    // ============================
    // Encode SINGLE STAGE
    // ============================
    template<std::size_t I>
    void encode(const MarsDict_t& mars,
                const GeoDict_t& geo,
                const ParDict_t& par,
                const OptDict_t& opt,
                OutDict_t& out) const
    {
#if 0
        OutDict_t sample(out);

        static_assert(I < NUM_STAGES, "Stage index out of range");

        if constexpr (I == 0) {
            prepare(mars, opt, sample);
        }

        const auto& stageVecs = callbacks_[I];

        for (std::size_t secIdx = 0; secIdx < NUM_SECTIONS; ++secIdx) {
            const auto& fns = stageVecs[secIdx];
            for (Fn_t fn : fns) {
                fn(mars, geo, par, opt, sample);
            }
        }

        return sample;
#endif

    }

    // ============================
    // Encode ALL STAGES
    // ============================
    void encode(const MarsDict_t& mars,
                const GeoDict_t& geo,
                const ParDict_t& par,
                const OptDict_t& opt,
                OutDict_t& out ) const
    {
#if 0
        OutDict_t sample( cleanSample );

        prepare(mars, opt, sample);
        sample.safeReload();
#endif

        for (std::size_t stage = 0; stage < NUM_STAGES; ++stage) {
            const auto& stageVecs = callbacks_[stage];
            std::cout << std::endl << " + Stage: " << stage << std::endl;
            for (std::size_t secIdx = 0; secIdx < NUM_SECTIONS; ++secIdx) {
                const auto& fns = stageVecs[secIdx];
                std::cout << "    + Section: " << secIdx << std::endl;
                for (Fn_t fn : fns) {
                    std::cout << "       - ";
                    fn(mars, geo, par, opt, out);
                }
            }

            // sample.safeReload();
        }

        return;


    }

private:
    const utils::EncoderCfg cfg_;
    const Callbacks callbacks_;

private:

    void prepare(const MarsDict_t& mars,
                 const OptDict_t& opt,
                 OutDict_t& out) const
    {
        // Prepare the output dictionary for encoding
    }
};


}