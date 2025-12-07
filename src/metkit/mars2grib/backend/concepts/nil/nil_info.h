#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "nil_enum.h"
#include "nil_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct NilConceptInfo
{
    static constexpr const char* name = "nil";

    template<
        int Stage, int Sec,
        NilType Variant,
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
        if constexpr ( nilApplicable(Stage, Sec, Variant) ) {
            return &NilOp<
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
            nilTypeName<
                static_cast<NilType>(Variant)
            >()
        );
    }
};
