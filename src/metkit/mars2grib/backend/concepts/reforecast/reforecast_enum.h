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
enum class ReforecastType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using ReforecastList = ValueList<
    ReforecastType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<ReforecastType T>
constexpr std::string_view reforecastTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view reforecastTypeName<T>() { return NAME; }

    DEF(ReforecastType::Default, "default");

#undef DEF
