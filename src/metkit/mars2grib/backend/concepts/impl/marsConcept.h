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
enum class MarsType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using MarsList = ValueList<
    MarsType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<MarsType T>
constexpr std::string_view marsTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view marsTypeName<T>() { return NAME; }

    DEF(MarsType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool marsApplicable(int Stage, int Section, MarsType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    MarsType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t MarsOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Mars] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(marsTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct MarsConceptInfo
{
    static constexpr const char* name = "mars";

    template<
        int Stage, int Sec,
        MarsType Variant,
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
        if constexpr ( marsApplicable(Stage, Sec, Variant) ) {
            return &MarsOp<
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
            marsTypeName<
                static_cast<MarsType>(Variant)
            >()
        );
    }
};
