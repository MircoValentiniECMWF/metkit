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
enum class ParamType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using ParamList = ValueList<
    ParamType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<ParamType T>
constexpr std::string_view paramTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view paramTypeName<T>() { return NAME; }

    DEF(ParamType::Default, "default");

#undef DEF
