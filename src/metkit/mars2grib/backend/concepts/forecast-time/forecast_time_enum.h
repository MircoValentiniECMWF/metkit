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
enum class ForecastTimeType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using ForecastTimeList = ValueList<
    ForecastTimeType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<ForecastTimeType T>
constexpr std::string_view forecast_timeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view forecast_timeTypeName<T>() { return NAME; }

    DEF(ForecastTimeType::Default, "default");

#undef DEF
