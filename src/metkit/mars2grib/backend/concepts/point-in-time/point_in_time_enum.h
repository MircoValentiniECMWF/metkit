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
enum class PointInTimeType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using PointInTimeList = ValueList<
    PointInTimeType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<PointInTimeType T>
constexpr std::string_view point_in_timeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view point_in_timeTypeName<T>() { return NAME; }

    DEF(PointInTimeType::Default, "default");

#undef DEF
