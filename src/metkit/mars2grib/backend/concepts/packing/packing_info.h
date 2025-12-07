#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "packing_enum.h"
#include "packing_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct PackingConceptInfo
{
    static constexpr const char* name = "packing";

    template<
        int Stage, int Sec,
        PackingType Variant,
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
        if constexpr ( packingApplicable(Stage, Sec, Variant) ) {
            return &PackingOp<
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
            packingTypeName<
                static_cast<PackingType>(Variant)
            >()
        );
    }
};
