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
enum class AnalysisType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using AnalysisList = ValueList<
    AnalysisType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<AnalysisType T>
constexpr std::string_view analysisTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view analysisTypeName<T>() { return NAME; }

    DEF(AnalysisType::Default, "default");

#undef DEF
