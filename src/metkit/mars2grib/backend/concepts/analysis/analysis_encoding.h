#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "analysis_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool analysisApplicable(int Stage, int Section, AnalysisType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    AnalysisType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t AnalysisOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Analysis] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(analysisTypeName<Variant>())
              << std::endl;
    return 0;
}
