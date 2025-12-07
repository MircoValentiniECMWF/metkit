#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "satellite_enum.h"
#include "satellite_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct SatelliteConceptInfo
{
    static constexpr const char* name = "satellite";

    template<
        int Stage, int Sec,
        SatelliteType Variant,
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
        if constexpr ( satelliteApplicable(Stage, Sec, Variant) ) {
            return &SatelliteOp<
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
    }

    template<auto Variant>
    static std::string_view variantName()
    {
        return std::string_view(
            satelliteTypeName<
                static_cast<SatelliteType>(Variant)
            >()
        );
    }
};
