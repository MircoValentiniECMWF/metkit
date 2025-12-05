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
enum class LongrangeType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using LongrangeList = ValueList<
    LongrangeType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<LongrangeType T>
constexpr std::string_view longrangeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view longrangeTypeName<T>() { return NAME; }

    DEF(LongrangeType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool longrangeApplicable(int Stage, int Section, LongrangeType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    LongrangeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t LongrangeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Longrange] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(longrangeTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct LongrangeConceptInfo
{
    static constexpr const char* name = "longrange";

    template<
        int Stage, int Sec,
        LongrangeType Variant,
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
        if constexpr ( longrangeApplicable(Stage, Sec, Variant) ) {
            return &LongrangeOp<
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
            longrangeTypeName<
                static_cast<LongrangeType>(Variant)
            >()
        );
    }
};
