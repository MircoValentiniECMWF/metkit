#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "generating_process_enum.h"
#include "generating_process_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct GeneratingProcessConceptInfo
{
    static constexpr const char* name = "generatingProcess";

    template<
        int Stage, int Sec,
        GeneratingProcessType Variant,
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
        if constexpr ( generating_processApplicable(Stage, Sec, Variant) ) {
            return &GeneratingProcessOp<
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
            generating_processTypeName<
                static_cast<GeneratingProcessType>(Variant)
            >()
        );
    }
};
