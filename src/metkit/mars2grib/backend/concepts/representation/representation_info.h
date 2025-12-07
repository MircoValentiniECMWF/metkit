#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "representation_enum.h"
#include "representation_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct RepresentationConceptInfo
{
    static constexpr const char* name = "representation";

    template<
        int Stage, int Sec,
        RepresentationType Variant,
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
        if constexpr ( representationApplicable(Stage, Sec, Variant) ) {
            return &RepresentationOp<
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
            representationTypeName<
                static_cast<RepresentationType>(Variant)
            >()
        );
    }
};
