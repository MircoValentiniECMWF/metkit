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
enum class LongrangeType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using LongrangeList = ValueList<
    LongrangeType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<LongrangeType T>
constexpr std::string_view longrangeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view longrangeTypeName<T>() { return NAME; }

    DEF(LongrangeType::Default, "default");

#undef DEF
