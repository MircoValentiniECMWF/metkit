#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "ensemble_enum.h"
#include "ensemble_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct EnsembleConceptInfo
{
    static constexpr const char* name = "ensemble";

    template<
        int Stage, int Sec,
        EnsembleType Variant,
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
        if constexpr ( ensembleApplicable(Stage, Sec, Variant) ) {
            return &EnsembleOp<
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
            ensembleTypeName<
                static_cast<EnsembleType>(Variant)
            >()
        );
    }
};
