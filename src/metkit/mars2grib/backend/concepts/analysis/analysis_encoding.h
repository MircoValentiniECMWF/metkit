#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <array>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/analysis/analysis_enum.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/lengthOfTimeWindow.h"

namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool analysisApplicable(StageType Stage, SectionType Section, AnalysisType Variant)
{

    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
      (Variant == AnalysisType::Default),
      (Stage == StageType::Preset),
      (Section == SectionType::LocalUseSection)
    }};

    // Conditions to apply concept
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
    StageType Stage, SectionType Section,
    AnalysisType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t AnalysisOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{

    // eccodes/definitions/grib2/local.98.36.def
    if constexpr ( analysisApplicable(Stage, Section, Variant) ) {


        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
              << "[Concept Analysis] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(analysisTypeName<Variant>())
              << std::endl;

        // =============================================================
        // Preconditions/contracts for this concept
        has_or_throw<ConceptException>( out, "localUsePresent",
            [](){ return "Missing `localDefinitionNumber` in grib Header"; },
            Here()
        );

        check_or_throw<long,ConceptException>( out, "localDefinitionNumber",
            []( long& v ){
                if ( v != 36 ) {
                    throw ConceptException("localDefinitionNumber is not 36", Here());
                };
                return true;
            }
        );

        // =============================================================
        // Mandatory operations
        // Forward "anoffset" from mars to grib sample
        forward_or_throw<long, long, ConceptException>(
            mars, out, "anoffset", "offsetToEndOf4DvarWindow", Here()
        );

        // =============================================================
        // Conditional operations
        // Forward "length of time window" from parametrization to grib sample
        // (Number must be in hours)
        // TODO MIVAL: this needs to be improved. Currently this function
        // rely on what is in the initial sample, but ideally we should
        // compute it somehow
        if (  auto lengthOfTimeWindowOpt = deductions::lengthOfTimeWindow<MarsDict_t,ParDict_t>( mars, par ); lengthOfTimeWindowOpt.has_value() ) {
            set_or_throw<ConceptException>( out, "lengthOfTimeWindow",
                long(lengthOfTimeWindowOpt.value()),
                [&lengthOfTimeWindowOpt](){ return "`lengthOfTimeWindow` could not be set to the grib header with value: " + std::to_string(lengthOfTimeWindowOpt.value()); },
                Here()
            );
        }

        // Successful operation
        return 0;

    }

    // Operation not applicable
    return 1;
}

}  // namespace metkit::mars2grib::backend