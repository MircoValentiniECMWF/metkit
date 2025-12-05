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
enum class PackingType : int {
    Gridsimple = 0,
    Ccsds = 1,
    Spectralcomplex = 2
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using PackingList = ValueList<
    PackingType::Gridsimple,
    PackingType::Ccsds,
    PackingType::Spectralcomplex
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<PackingType T>
constexpr std::string_view packingTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view packingTypeName<T>() { return NAME; }

    DEF(PackingType::Gridsimple, "GridSimple");
    DEF(PackingType::Ccsds, "Ccsds");
    DEF(PackingType::Spectralcomplex, "SpectralComplex");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool packingApplicable(int Stage, int Section, PackingType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    PackingType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t PackingOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Packing] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(packingTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct PackingConceptInfo
{
    static constexpr const char* name = "packing";

    template<
        int Stage, int Sec,
        PackingType Variant,
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
        if constexpr ( packingApplicable(Stage, Sec, Variant) ) {
            return &PackingOp<
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
            packingTypeName<
                static_cast<PackingType>(Variant)
            >()
        );
    }
};
