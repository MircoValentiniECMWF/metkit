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
enum class GridtypeType : int {
    Regularll = 0,
    Reducedgg = 1,
    Sphericalharmonics = 2,
    Healpix = 3,
    Orca = 4,
    Fesom = 5
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using GridtypeList = ValueList<
    GridtypeType::Regularll,
    GridtypeType::Reducedgg,
    GridtypeType::Sphericalharmonics,
    GridtypeType::Healpix,
    GridtypeType::Orca,
    GridtypeType::Fesom
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<GridtypeType T>
constexpr std::string_view gridtypeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view gridtypeTypeName<T>() { return NAME; }

    DEF(GridtypeType::Regularll, "RegularLL");
    DEF(GridtypeType::Reducedgg, "ReducedGG");
    DEF(GridtypeType::Sphericalharmonics, "SphericalHarmonics");
    DEF(GridtypeType::Healpix, "HEALPix");
    DEF(GridtypeType::Orca, "ORCA");
    DEF(GridtypeType::Fesom, "Fesom");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool gridtypeApplicable(int Stage, int Section, GridtypeType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    GridtypeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t GridtypeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Gridtype] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(gridtypeTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct GridtypeConceptInfo
{
    static constexpr const char* name = "gridtype";

    template<
        int Stage, int Sec,
        GridtypeType Variant,
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
        if constexpr ( gridtypeApplicable(Stage, Sec, Variant) ) {
            return &GridtypeOp<
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
            gridtypeTypeName<
                static_cast<GridtypeType>(Variant)
            >()
        );
    }
};
