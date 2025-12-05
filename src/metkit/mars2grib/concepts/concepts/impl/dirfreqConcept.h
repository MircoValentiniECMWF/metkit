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
enum class DirfreqType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using DirfreqList = ValueList<
    DirfreqType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<DirfreqType T>
constexpr std::string_view dirfreqTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view dirfreqTypeName<T>() { return NAME; }

    DEF(DirfreqType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool dirfreqApplicable(int Stage, int Section, DirfreqType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    DirfreqType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t DirfreqOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Dirfreq] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(dirfreqTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct DirfreqConceptInfo
{
    static constexpr const char* name = "dirfreq";

    template<
        int Stage, int Sec,
        DirfreqType Variant,
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
        if constexpr ( dirfreqApplicable(Stage, Sec, Variant) ) {
            return &DirfreqOp<
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
            dirfreqTypeName<
                static_cast<DirfreqType>(Variant)
            >()
        );
    }
};
