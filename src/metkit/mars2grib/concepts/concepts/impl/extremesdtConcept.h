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
enum class ExtremesdtType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using ExtremesdtList = ValueList<
    ExtremesdtType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<ExtremesdtType T>
constexpr std::string_view extremesdtTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view extremesdtTypeName<T>() { return NAME; }

    DEF(ExtremesdtType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool extremesdtApplicable(int Stage, int Section, ExtremesdtType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    ExtremesdtType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t ExtremesdtOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Extremesdt] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(extremesdtTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct ExtremesdtConceptInfo
{
    static constexpr const char* name = "extremesdt";

    template<
        int Stage, int Sec,
        ExtremesdtType Variant,
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
        if constexpr ( extremesdtApplicable(Stage, Sec, Variant) ) {
            return &ExtremesdtOp<
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
    static std::string variantName()
    {
        return std::string(
            extremesdtTypeName<
                static_cast<ExtremesdtType>(Variant)
            >()
        );
    }
};
