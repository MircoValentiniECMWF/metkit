#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <array>
#include <exception>


// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/origin/origin_enum.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/mars-origin.h"
#include "metkit/mars2grib/backend/deductions/subCentre.h"

// Exceptions
#include "metkit/mars2grib/utils/mars2grib-exception.h"

namespace metkit::mars2grib::backend::cnpts {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool originApplicable(uint8_t Stage, uint8_t Section, OriginType Variant)
{

    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
      (Variant == OriginType::Default),
      (Stage == StageType::Preset),
      (Section == SectionType::LocalUseSection)
    }};

    // Confitions to apply concept
    return std::all_of(
        conditions.begin(),
        conditions.end(),
        [](bool b){ return b; }
    );

}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    OriginType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
void OriginOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out) noexcept(false)
{

    if constexpr ( originApplicable(Stage, Section, Variant) ) {

        try {

            LOG_DEBUG_LIB(LibMetkit)
                << "[Concept Origin] Op called: "
                << "Stage="   << Stage
                << ", Section=" << Section
                << ", Variant=" << std::string(originTypeName<Variant>())
                << std::endl;

            std::string origin = deductions::mars_origin( mars, par );
            long subCentre = deductions::sub_centre( mars, par );

            set_or_throw<std::string>( out, "origin", origin );
            set_or_throw<long>( out, "subCentre", subCentre );

        }
        catch ( ... ){

            // Rethrow nested exceptions
            std::rethrow_with_nested(
                utils::Mars2gGibConceptException(
                    std::string( originName ),
                    std::string( originTypeName(Variant) ),
                    std::to_string(static_cast<uint8_t>(Stage)),
                    std::to_string(static_cast<uint8_t>(Section)),
                    "Unable to set `origin` concept...",
                    Here()
                )
            );

        }

        // Successful operation
        return;

    } // if constexpr ( originApplicable(Stage, Section, Variant) )

    // Paranoid check. Should never arrive here
    throw utils::Mars2gGibConceptException(
            std::string( originName ),
            std::string( originTypeName(Variant) ),
            std::to_string(static_cast<uint8_t>(Stage)),
            std::to_string(static_cast<uint8_t>(Section)),
            "Concept called when not applicable...",
            Here()
        );

    // Remove compiler warning
    __builtin_unreachable();

}

}  // namespace metkit::mars2grib::backend::cnpts