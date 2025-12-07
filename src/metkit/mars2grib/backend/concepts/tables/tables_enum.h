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
