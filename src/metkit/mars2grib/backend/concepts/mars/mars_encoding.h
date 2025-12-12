#pragma once

#include <string>
#include <string_view>
#include <iostream>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/mars/mars_enum.h"

namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool marsApplicable(int Stage, int Section, MarsType Variant)
{

    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
      (Variant == MarsType::Default),
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
    MarsType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t MarsOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{

    // eccodes/definitions/grib2/local.98.36.def
    if constexpr ( marsApplicable(Stage, Section, Variant) ) {


        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
            << "[Concept Mars] Op called: "
            << "Stage="   << Stage
            << ", Section=" << Section
            << ", Variant=" << std::string(marsTypeName<Variant>())
            << std::endl;

        // =============================================================
        // Preconditions/contracts for this concept
        has_or_throw<ConceptException>( out, "localUsePresent",
            [](){ return "Missing `localDefinitionNumber` in grib Header"; },
            Here()
        );


        // =============================================================
        // Get values from input MARS dictionary
        std::string classVal  = get_mars_or_throw<std::string,ConceptException>( mars, "class", Here() );
        std::string typeVal   = get_mars_or_throw<std::string,ConceptException>( mars, "type", Here() );
        std::string streamVal = get_mars_or_throw<std::string,ConceptException>( mars, "stream", Here() );
        std::string expverVal = get_mars_or_throw<std::string,ConceptException>( mars, "expver", Here() );

        // =============================================================
        // Set values in output dictionary
        set_or_throw<long,ConceptException>(
            out, "class", classVal,
            [&classVal](){ "`class` could not be set to the grib header with value: " + std::to_string(classVal); },
            Here()
        );

        set_or_throw<long,ConceptException>(
            out, "type", typeVal,
            [&typeVal](){ "`type` could not be set to the grib header with value: " + std::to_string(typeVal); },
            Here()
        );

        set_or_throw<long,ConceptException>(
            out, "stream", streamVal,
            [&streamVal](){ "`stream` could not be set to the grib header with value: " + std::to_string(streamVal); },
            Here()
        );

        set_or_throw<long,ConceptException>(
            out, "expver", expverVal,
            [&expverVal](){ "`expver` could not be set to the grib header with value: " + std::to_string(expverVal); },
            Here()
        );


        // Successful operation
        return 0;

    }

    // Operation not applicable
    return 1;
}

} // namespace metkit::mars2grib::backend