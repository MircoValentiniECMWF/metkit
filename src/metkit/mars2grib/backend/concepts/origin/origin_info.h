#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "origin_enum.h"
#include "origin_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct OriginConceptInfo
{
    static constexpr const char* name = "origin";

    template<
        int Stage, int Sec,
        OriginType Variant,
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
        if constexpr ( originApplicable(Stage, Sec, Variant) ) {
            return &OriginOp<
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
            originTypeName<
                static_cast<OriginType>(Variant)
            >()
        );
    }
};
