#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "shape_of_the_earth_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool shape_of_the_earthApplicable(int Stage, int Section, ShapeOfTheEarthType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    ShapeOfTheEarthType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t ShapeOfTheEarthOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept ShapeOfTheEarth] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(shape_of_the_earthTypeName<Variant>())
              << std::endl;
    return 0;
}
