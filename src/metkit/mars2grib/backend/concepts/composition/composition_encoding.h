#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "composition_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool compositionApplicable(int Stage, int Section, CompositionType Variant)
{
    return true;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    CompositionType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t CompositionOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Composition] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(compositionTypeName<Variant>())
              << std::endl;
    return 0;
}
