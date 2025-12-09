#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "tables_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool tablesApplicable(int Stage, int Section, TablesType Variant)
{
    return true;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    TablesType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t TablesOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Tables] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(tablesTypeName<Variant>())
              << std::endl;
    return 0;
}
