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
enum class ShapeOfTheEarthType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using ShapeOfTheEarthList = ValueList<
    ShapeOfTheEarthType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<ShapeOfTheEarthType T>
constexpr std::string_view shape_of_the_earthTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view shape_of_the_earthTypeName<T>() { return NAME; }

    DEF(ShapeOfTheEarthType::Default, "default");

#undef DEF
