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
enum class CompositionType : int {
    Chem = 0,
    Aerosol,
    AerosolOptical,
    ChemicalSource,
    AerosolOpticalSource,
    Default
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using CompositionList = ValueList<
    CompositionType::Chem,
    CompositionType::Aerosol,
    CompositionType::AerosolOptical,
    CompositionType::ChemicalSource,
    CompositionType::AerosolOpticalSource,
    CompositionType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<CompositionType T>
constexpr std::string_view compositionTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view compositionTypeName<T>() { return NAME; }

    DEF(CompositionType::Chem, "chem");
    DEF(CompositionType::Aerosol, "aerosol");
    DEF(CompositionType::AerosolOptical, "aerosolOptical");
    DEF(CompositionType::ChemicalSource, "chemicalSource");
    DEF(CompositionType::AerosolOpticalSource, "aerosolOpticalSource");
    DEF(CompositionType::Default, "default");

#undef DEF
