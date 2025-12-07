#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "point_in_time_enum.h"
#include "point_in_time_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct PointInTimeConceptInfo
{
    static constexpr const char* name = "pointInTime";

    template<
        int Stage, int Sec,
        PointInTimeType Variant,
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
        if constexpr ( point_in_timeApplicable(Stage, Sec, Variant) ) {
            return &PointInTimeOp<
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
            point_in_timeTypeName<
                static_cast<PointInTimeType>(Variant)
            >()
        );
    }
};
