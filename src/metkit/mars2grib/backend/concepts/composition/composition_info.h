#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "composition_enum.h"
#include "composition_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct CompositionConceptInfo
{
    static constexpr const char* name = "composition";

    template<
        int Stage, int Sec,
        CompositionType Variant,
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
        if constexpr ( compositionApplicable(Stage, Sec, Variant) ) {
            return &CompositionOp<
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
            compositionTypeName<
                static_cast<CompositionType>(Variant)
            >()
        );
    }
};
