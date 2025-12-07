#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "level_enum.h"
#include "level_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct LevelConceptInfo
{
    static constexpr const char* name = "level";

    template<
        int Stage, int Sec,
        LevelType Variant,
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
        if constexpr ( levelApplicable(Stage, Sec, Variant) ) {
            return &LevelOp<
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
            levelTypeName<
                static_cast<LevelType>(Variant)
            >()
        );
    }
};
