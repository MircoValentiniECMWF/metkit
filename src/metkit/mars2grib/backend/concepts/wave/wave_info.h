#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "wave_enum.h"
#include "wave_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct WaveConceptInfo
{
    static constexpr const char* name = "wave";

    template<
        int Stage, int Sec,
        WaveType Variant,
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
        if constexpr ( waveApplicable(Stage, Sec, Variant) ) {
            return &WaveOp<
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
            waveTypeName<
                static_cast<WaveType>(Variant)
            >()
        );
    }
};
