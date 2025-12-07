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
