#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "reforecast_enum.h"
#include "reforecast_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct ReforecastConceptInfo
{
    static constexpr const char* name = "reforecast";

    template<
        int Stage, int Sec,
        ReforecastType Variant,
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
        if constexpr ( reforecastApplicable(Stage, Sec, Variant) ) {
            return &ReforecastOp<
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
            reforecastTypeName<
                static_cast<ReforecastType>(Variant)
            >()
        );
    }
};
