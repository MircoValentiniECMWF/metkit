#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <iostream>

#include "metkit/mars2grib/backend/concepts/concept_core.h"

namespace metkit::mars2grib::backend::cnpts {

// ======================================================
// NAME OF THE CONCEPT
// ======================================================
constexpr inline std::string_view originName{"origin"};

// ======================================================
// ENUM OF VARIANTS FOR THIS CONCEPT
// ======================================================
enum class OriginType : uint8_t {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using OriginList = ValueList<
    OriginType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
inline constexpr std::string_view originName{"origin"};

template<OriginType T>
constexpr std::string_view originTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view originTypeName<T>() { return NAME; }

    DEF(OriginType::Default, "default");

#undef DEF

}  // namespace metkit::mars2grib::backend::cnpts
