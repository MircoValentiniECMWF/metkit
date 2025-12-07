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
enum class OriginType : int {
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
template<OriginType T>
constexpr std::string_view originTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view originTypeName<T>() { return NAME; }

    DEF(OriginType::Default, "default");

#undef DEF
