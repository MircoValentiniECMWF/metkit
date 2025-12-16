#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <iostream>

#include "metkit/mars2grib/backend/concepts/concept_core.h"

// Exceptions
#include "metkit/mars2grib/utils/mars2grib-exception.h"

namespace metkit::mars2grib::backend::cnpts {

// ======================================================
// NAME OF THE CONCEPT
// ======================================================
inline constexpr std::string_view forecastTimeName{"forecastTime"};

// ======================================================
// ENUM OF VARIANTS FOR THIS CONCEPT
// ======================================================
enum class ForecastTimeType : std::size_t {
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
constexpr std::string_view forecastTimeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view forecastTimeTypeName<T>() { return NAME; }

    DEF(ForecastTimeType::Default, "default");

#undef DEF

} // namespace metkit::mars2grib::backend::cnpts