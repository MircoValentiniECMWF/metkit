#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/nil/nil_enum.h"

namespace metkit::mars2grib::backend::cnpts {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool nilApplicable(int Stage, int Section, NilType Variant)
{
    return true;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    NilType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
[[noreturn]]
void NilOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out) noexcept(false)
{
    std::cout << "[Concept Nil] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(nilTypeName<Variant>())
              << std::endl;
    return;
}

} // namespace metkit::mars2grib::backend::cnpts