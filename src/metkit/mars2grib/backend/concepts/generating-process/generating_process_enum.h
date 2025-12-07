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
enum class GeneratingProcessType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using GeneratingProcessList = ValueList<
    GeneratingProcessType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<GeneratingProcessType T>
constexpr std::string_view generating_processTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view generating_processTypeName<T>() { return NAME; }

    DEF(GeneratingProcessType::Default, "default");

#undef DEF
