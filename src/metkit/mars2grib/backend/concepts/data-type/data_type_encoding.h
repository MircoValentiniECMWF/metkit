#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "data_type_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool data_typeApplicable(int Stage, int Section, DataTypeType Variant)
{
    return true;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    DataTypeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t DataTypeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept DataType] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(data_typeTypeName<Variant>())
              << std::endl;
    return 0;
}
