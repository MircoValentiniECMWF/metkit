#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <iostream>

#include "../concept_core.h"

// ======================================================
// ENUM OF VARIANTS FOR THIS CONCEPT
// ======================================================
enum class ReferencetimeType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using ReferencetimeList = ValueList<
    ReferencetimeType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<ReferencetimeType T>
constexpr std::string_view referencetimeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view referencetimeTypeName<T>() { return NAME; }

    DEF(ReferencetimeType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool referencetimeApplicable(int Stage, int Section, ReferencetimeType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    ReferencetimeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t ReferencetimeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Referencetime] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(referencetimeTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct ReferencetimeConceptInfo
{
    static constexpr const char* name = "referencetime";

    template<
        int Stage, int Sec,
        ReferencetimeType Variant,
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
        if constexpr ( referencetimeApplicable(Stage, Sec, Variant) ) {
            return &ReferencetimeOp<
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
            referencetimeTypeName<
                static_cast<ReferencetimeType>(Variant)
            >()
        );
    }
};
