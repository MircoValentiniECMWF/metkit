#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "tables_enum.h"
#include "tables_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct TablesConceptInfo
{
    static constexpr const char* name = "tables";

    template<
        int Stage, int Sec,
        TablesType Variant,
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
        if constexpr ( tablesApplicable(Stage, Sec, Variant) ) {
            return &TablesOp<
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
            tablesTypeName<
                static_cast<TablesType>(Variant)
            >()
        );
    }
};
