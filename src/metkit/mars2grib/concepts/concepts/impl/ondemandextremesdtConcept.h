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
enum class OndemandextremesdtType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using OndemandextremesdtList = ValueList<
    OndemandextremesdtType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<OndemandextremesdtType T>
constexpr std::string_view ondemandextremesdtTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view ondemandextremesdtTypeName<T>() { return NAME; }

    DEF(OndemandextremesdtType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool ondemandextremesdtApplicable(int Stage, int Section, OndemandextremesdtType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    OndemandextremesdtType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t OndemandextremesdtOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Ondemandextremesdt] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(ondemandextremesdtTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct OndemandextremesdtConceptInfo
{
    static constexpr const char* name = "ondemandextremesdt";

    template<
        int Stage, int Sec,
        OndemandextremesdtType Variant,
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
        if constexpr ( ondemandextremesdtApplicable(Stage, Sec, Variant) ) {
            return &OndemandextremesdtOp<
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
            ondemandextremesdtTypeName<
                static_cast<OndemandextremesdtType>(Variant)
            >()
        );
    }
};
