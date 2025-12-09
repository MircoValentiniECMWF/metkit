#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "mars_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool marsApplicable(int Stage, int Section, MarsType Variant)
{
    return true;
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
