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
enum class MarsType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using MarsList = ValueList<
    MarsType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<MarsType T>
constexpr std::string_view marsTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view marsTypeName<T>() { return NAME; }

    DEF(MarsType::Default, "default");

#undef DEF

} // namespace metkit::mars2grib::backend