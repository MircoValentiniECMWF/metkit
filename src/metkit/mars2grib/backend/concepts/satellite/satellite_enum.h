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
enum class SatelliteType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using SatelliteList = ValueList<
    SatelliteType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<SatelliteType T>
constexpr std::string_view satelliteTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view satelliteTypeName<T>() { return NAME; }

    DEF(SatelliteType::Default, "default");

#undef DEF
