#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "longrange_enum.h"
#include "longrange_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct LongrangeConceptInfo
{
    static constexpr const char* name = "longrange";

    template<
        int Stage, int Sec,
        LongrangeType Variant,
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
        if constexpr ( longrangeApplicable(Stage, Sec, Variant) ) {
            return &LongrangeOp<
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
            longrangeTypeName<
                static_cast<LongrangeType>(Variant)
            >()
        );
    }
};
