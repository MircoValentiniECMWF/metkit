#pragma once

#include <string>
#include <string_view>
#include <iostream>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/destine/destine_enum.h"

namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool destineApplicable(int Stage, int Section, DestineType Variant)
{
    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
      (Variant == DestineType::ClimateDT || Variant == DestineType::ExtremesDT),
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
    DestineType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t DestineOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{

    // eccodes/definitions/grib2/local.98.36.def
    if constexpr ( destineApplicable(Stage, Section, Variant) ) {


        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
            << "[Concept Destine] Op called: "
            << "Stage="   << Stage
            << ", Section=" << Section
            << ", Variant=" << std::string(destineTypeName<Variant>())
            << std::endl;

        // =============================================================
        // Preconditions/contracts for this concept
        has_or_throw<ConceptException>( out, "localUsePresent",
            [](){ return "Missing `localDefinitionNumber` in grib Header"; },
            Here()
        );

        check_or_throw<long,ConceptException>( out, "productionStatusOfProcessedData",
            []( long& v ){
                if ( v != 12 ) {
                    throw ConceptException("`productionStatusOfProcessedData` is not 12", Here());
                };
                return true;
            }
        );


        // =============================================================
        // Get values from input MARS dictionary
        std::string datasetVal  = get_mars_or_throw<std::string,ConceptException>( mars, "dataset", Here() );


        if constexpr ( Variant == DestineType::ExtremesDT )  {

            if ( datasetVal != "extremes-dt" ) {
                throw ConceptException("`dataset` is not `extremes-dt` for ExtremesDT variant", Here());
            }

            // =============================================================
            // Set values in output dictionary
            set_or_throw<long,ConceptException>(
                out, "dataset", datasetVal,
                [&datasetVal](){ "`dataset` could not be set to the grib header with value: " + std::to_string(datasetVal); },
                Here()
            );

        }
        else if constexpr ( Variant == DestineType::ClimateDT )  {

            if ( datasetVal != "climate-dt" ) {
                throw ConceptException("`dataset` is not `climate-dt` for ClimateDT variant", Here());
            }

            // =============================================================
            // Set values in output dictionary
            set_or_throw<long,ConceptException>(
                out, "dataset", datasetVal,
                [&datasetVal](){ "`dataset` could not be set to the grib header with value: " + std::to_string(datasetVal); },
                Here()
            );

            // RRead mars keywords from dictionary
            std::string activityVal    = get_mars_or_throw<std::string,ConceptException>( mars, "activity", Here() );
            std::string experimentVal  = get_mars_or_throw<std::string,ConceptException>( mars, "experiment", Here() );
            std::string resolutionVal  = get_mars_or_throw<std::string,ConceptException>( mars, "resolution", Here() );
            std::string generationVal  = get_mars_or_throw<std::string,ConceptException>( mars, "generation", Here() );
            std::string realizationVal = get_mars_or_throw<std::string,ConceptException>( mars, "realization", Here() );

            // Set values in output dictionary
            set_or_throw<long,ConceptException>(
                out, "activity", activityVal,
                [&activityVal](){ "`activity` could not be set to the grib header with value: " + std::to_string(activityVal); },
                Here()
            );
            set_or_throw<long,ConceptException>(
                out, "experiment", experimentVal,
                [&experimentVal](){ "`experiment` could not be set to the grib header with value: " + std::to_string(experimentVal); },
                Here()
            );
            set_or_throw<long,ConceptException>(
                out, "resolution", resolutionVal,
                [&resolutionVal](){ "`resolution` could not be set to the grib header with value: " + std::to_string(resolutionVal); },
                Here()
            );
            set_or_throw<long,ConceptException>(
                out, "generation", generationVal,
                [&generationVal](){ "`generation` could not be set to the grib header with value: " + std::to_string(generationVal); },
                Here()
            );
            set_or_throw<long,ConceptException>(
                out, "realization", realizationVal,
                [&realizationVal](){ "`realization` could not be set to the grib header with value: " + std::to_string(realizationVal); },
                Here()
            );

        }

        // Successful operation
        return 0;

    }

    // Operation not applicable
    return 1;

}

} // namespace metkit::mars2grib::backend
