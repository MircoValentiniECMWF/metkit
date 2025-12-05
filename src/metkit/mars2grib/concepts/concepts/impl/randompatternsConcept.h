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
enum class RandompatternsType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using RandompatternsList = ValueList<
    RandompatternsType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<RandompatternsType T>
constexpr std::string_view randompatternsTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view randompatternsTypeName<T>() { return NAME; }

    DEF(RandompatternsType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool randompatternsApplicable(int Stage, int Section, RandompatternsType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    RandompatternsType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t RandompatternsOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Randompatterns] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(randompatternsTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct RandompatternsConceptInfo
{
    static constexpr const char* name = "randompatterns";

    template<
        int Stage, int Sec,
        RandompatternsType Variant,
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
        if constexpr ( randompatternsApplicable(Stage, Sec, Variant) ) {
            return &RandompatternsOp<
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
            randompatternsTypeName<
                static_cast<RandompatternsType>(Variant)
            >()
        );
    }
};
