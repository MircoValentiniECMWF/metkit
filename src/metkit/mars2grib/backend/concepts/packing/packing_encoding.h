#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "packing_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool packingApplicable(int Stage, int Section, PackingType Variant)
{
    return true;
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
