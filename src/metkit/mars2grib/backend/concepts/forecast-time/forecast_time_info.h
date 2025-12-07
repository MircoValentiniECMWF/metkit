#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "forecast_time_enum.h"
#include "forecast_time_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct ForecastTimeConceptInfo
{
    static constexpr const char* name = "forecastTime";

    template<
        int Stage, int Sec,
        ForecastTimeType Variant,
        class MarsDict_t,
        class GeoDict_t,
        class ParDict_t,
        class OptDict_t,
        class OutDict_t
    >
    static constexpr Fn<
        MarsDict_t,
        GeoDict_t,
        ParDict_t,
        OptDict_t,
        OutDict_t
    > entry()
    {
        if constexpr ( forecast_timeApplicable(Stage, Sec, Variant) ) {
            return &ForecastTimeOp<
                Stage, Sec, Variant,
                MarsDict_t,
                GeoDict_t,
                ParDict_t,
                OptDict_t,
                OutDict_t
            >;
        } else {
            return nullptr;
        }

        // Remove compiler warning
        return nullptr;
    }

    template<auto Variant>
    static std::string_view variantName()
    {
        return std::string_view(
            forecast_timeTypeName<
                static_cast<ForecastTimeType>(Variant)
            >()
        );
    }
};
