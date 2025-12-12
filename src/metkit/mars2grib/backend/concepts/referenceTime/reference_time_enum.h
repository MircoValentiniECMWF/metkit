#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <iostream>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"

namespace metkit::mars2grib::backend {


// ======================================================
// ENUM OF VARIANTS FOR THIS CONCEPT
// ======================================================
enum class TimeType : uint8_t {
    Standard = 0,
    Reforecast = 1
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using TimeList = ValueList<
    TimeType::Standard,
    TimeType::Reforecast
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<TimeType T>
constexpr std::string_view timeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view timeTypeName<T>() { return NAME; }

    DEF(TimeType::Standard,   "standard" );
    DEF(TimeType::Reforecast, "reforecast" );

#undef DEF

}  // namespace metkit::mars2grib::backend