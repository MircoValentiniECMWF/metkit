#pragma once

#include <string>
#include <string_view>
#include <iostream>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/longrange/longrange_enum.h"


namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool longrangeApplicable(int Stage, int Section, LongrangeType Variant)
{

    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
      (Variant == LongrangeType::Default),
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
    LongrangeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t LongrangeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    // eccodes/definitions/grib2/local.98.36.def
    if constexpr ( longrangeApplicable(Stage, Section, Variant) ) {


        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
            << "[Concept Longrange] Applying longrange encoding"
            << "Stage="   << Stage
            << ", Section=" << Section
            << ", Variant=" << std::string(longrangeTypeName<Variant>())
            << std::endl;

        // =============================================================
        // Preconditions/contracts for this concept
        has_or_throw<ConceptException>( out, "localUsePresent",
            [](){ return "Missing `localDefinitionNumber` in grib Header"; },
            Here()
        );

        check_or_throw<long,ConceptException>( out, "localDefinitionNumber",
            []( long& v ){
                if ( v != 15 ) {
                    throw ConceptException("localDefinitionNumber is not 15", Here());
                };
                return true;
            }
        );

        // =============================================================
        // Get values from input MARS dictionary
        auto methodVal = get_mars_or_throw<long,ConceptException>( mars, "method", Here() );
        auto systemVal = get_mars_or_throw<long,ConceptException>( mars, "system", Here() );


        // =============================================================
        // Set values in output GRIB dictionary
        set_or_throw<long,ConceptException>(
            out, "methodNumber", methodVal,
            [&methodVal](){ "`methodNumber` could not be set to the grib header with value: " + std::to_string(methodVal); },
            Here() );
        set_or_throw<long,ConceptException>(
            out, "systemNumber", systemVal,
            [&systemVal](){ "`systemNumber` could not be set to the grib header with value: " + std::to_string(systemVal); },
            Here() );

        // Successful operation
        return 0;

    }

    // Operation not applicable
    return 1;

}

} // namespace metkit::mars2grib::backend