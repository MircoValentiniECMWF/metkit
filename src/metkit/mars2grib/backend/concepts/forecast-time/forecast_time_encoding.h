#pragma once

#include <string>
#include <string_view>
#include <iostream>


#include <eckit/types/DateTime.h>
#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/forecast-time/forecast_time_enum.h"

// Utils
#include "metkit/mars2grib/utils/timeUtils.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/marsStepInSeconds.h"

// Exceptions
#include "metkit/mars2grib/utils/mars2grib-exception.h"

namespace metkit::mars2grib::backend::cnpts {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
template<
    std::size_t Stage,
    std::size_t Section,
    ForecastTimeType Variant
>
constexpr bool forecastTimeApplicable()
{
    bool condition1 = Stage == StageAllocate && Section == SecProductDefinitionSection;
    bool condition2 = Stage == StagePreset   && Section == SecProductDefinitionSection;
    bool condition3 = Stage == StageRuntime  && Section == SecProductDefinitionSection;

    return ( condition1 || condition2 || condition3 );
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    std::size_t Stage,
    std::size_t Section,
    ForecastTimeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
void ForecastTimeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{

    using metkit::mars2grib::utils::dict_traits::setMissing_or_throw;
    using metkit::mars2grib::utils::dict_traits::set_or_throw;
    using metkit::mars2grib::utils::exceptions::Mars2GribConceptException;
    using metkit::mars2grib::utils::time::TimeUnit;

    if constexpr ( forecastTimeApplicable<Stage, Section, Variant>() ) {

        try {

            // =============================================================
            // Logging
            LOG_DEBUG_LIB(LibMetkit)
              << "[Concept PointInTime] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(forecastTimeTypeName<Variant>())
              << std::endl;


            // =============================================================
            // Deduce the forecast time in seconds
            long marsStepInSeconds = deductions::marsStepInSeconds_or_throw( mars, par );

            // For the moment we don't support sub hourly steps
            if ( marsStepInSeconds % 3600 != 0 ) {
                throw Mars2GribConceptException(
                    std::string( forecastTimeName ),
                    std::string( forecastTimeTypeName<Variant>() ),
                    std::to_string(Stage),
                    std::to_string(Section),
                    "Only full hour steps are supported currently",
                    Here()
                );
            }
            long marsStepInHours = marsStepInSeconds / 3600;

            if constexpr ( Stage == StageAllocate ) {
                // Set forecast time in hours since reference time
                setMissing_or_throw( out, "hoursAfterDataCutoff" );
                setMissing_or_throw( out, "minutesAfterDataCutoff" );
            }

            if constexpr ( Stage == StagePreset ) {
                // Set forecast time in hours since reference time
                // TODO MIVAL: Duplicated enum between eccodes and metkit!!!!
                set_or_throw<long>( out, "forecastTimeInHours", static_cast<long>(TimeUnit::Hour) );
            }

            if constexpr ( Stage == StageRuntime ) {
                set_or_throw<long>( out, "forecastTime", marsStepInHours );
            }


        }
        catch ( ... ){
            // Rethrow nested exceptions
            std::throw_with_nested(
                Mars2GribConceptException(
                    std::string( forecastTimeName ),
                    std::string( forecastTimeTypeName<Variant>() ),
                    std::to_string(Stage),
                    std::to_string(Section),
                    "Unable to set `ensemble` concept...",
                    Here()
                )
            );

        }

        // Successful operation
        return;

    } // if constexpr ( longrangeApplicable(Stage, Section, Variant) )

    // Paranoid check. Should never arrive here
    throw Mars2GribConceptException(
            std::string( forecastTimeName ),
            std::string( forecastTimeTypeName<Variant>() ),
            std::to_string(Stage),
            std::to_string(Section),
            "Concept called when not applicable...",
            Here()
        );

    // Remove compiler warning
    __builtin_unreachable();

}

} // namespace metkit::mars2grib::backend::cnpts