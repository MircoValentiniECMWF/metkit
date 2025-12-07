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
    Simple = 0,
    Ccsds,
    SpectralComplex,
    Default
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using PackingList = ValueList<
    PackingType::Simple,
    PackingType::Ccsds,
    PackingType::SpectralComplex,
    PackingType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<PackingType T>
constexpr std::string_view packingTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view packingTypeName<T>() { return NAME; }

    DEF(PackingType::Simple, "simple");
    DEF(PackingType::Ccsds, "ccsds");
    DEF(PackingType::SpectralComplex, "spectral_complex");
    DEF(PackingType::Default, "default");

#undef DEF
