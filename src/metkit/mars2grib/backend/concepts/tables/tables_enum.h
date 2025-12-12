#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <iostream>


#include "metkit/mars2grib/backend/concepts/concept_core.h"

namespace metkit::mars2grib::backend::deductions {

// ======================================================
// ENUM OF VARIANTS FOR THIS CONCEPT
// ======================================================
enum class TablesType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using TablesList = ValueList<
    TablesType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<TablesType T>
constexpr std::string_view tablesTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view tablesTypeName<T>() { return NAME; }

    DEF(TablesType::Default, "default");

#undef DEF

} // namespace metkit::mars2grib::backend