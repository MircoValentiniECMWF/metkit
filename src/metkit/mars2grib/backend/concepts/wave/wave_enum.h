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
enum class WaveType : int {
    Spectra = 0,
    Period,
    Default
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using WaveList = ValueList<
    WaveType::Spectra,
    WaveType::Period,
    WaveType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<WaveType T>
constexpr std::string_view waveTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view waveTypeName<T>() { return NAME; }

    DEF(WaveType::Spectra, "spectra");
    DEF(WaveType::Period, "period");
    DEF(WaveType::Default, "default");

#undef DEF
