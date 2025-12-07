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
enum class DataTypeType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using DataTypeList = ValueList<
    DataTypeType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<DataTypeType T>
constexpr std::string_view data_typeTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view data_typeTypeName<T>() { return NAME; }

    DEF(DataTypeType::Default, "default");

#undef DEF
