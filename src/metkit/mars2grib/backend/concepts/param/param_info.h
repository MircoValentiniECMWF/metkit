#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "param_enum.h"
#include "param_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct ParamConceptInfo
{
    static constexpr const char* name = "param";

    template<
        int Stage, int Sec,
        ParamType Variant,
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
        if constexpr ( paramApplicable(Stage, Sec, Variant) ) {
            return &ParamOp<
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
            paramTypeName<
                static_cast<ParamType>(Variant)
            >()
        );
    }
};
