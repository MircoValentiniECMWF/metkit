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
enum class NilType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using NilList = ValueList<
    NilType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<NilType T>
constexpr std::string_view nilTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view nilTypeName<T>() { return NAME; }

    DEF(NilType::Default, "default");

#undef DEF
