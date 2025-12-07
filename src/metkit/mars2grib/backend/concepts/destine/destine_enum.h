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
enum class DestineType : int {
    ClimateDT = 0,
    ExtremesDT,
    OnDemandExtremesDT,
    Default
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using DestineList = ValueList<
    DestineType::ClimateDT,
    DestineType::ExtremesDT,
    DestineType::OnDemandExtremesDT,
    DestineType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<DestineType T>
constexpr std::string_view destineTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view destineTypeName<T>() { return NAME; }

    DEF(DestineType::ClimateDT, "climateDT");
    DEF(DestineType::ExtremesDT, "extremesDT");
    DEF(DestineType::OnDemandExtremesDT, "onDemandExtremesDT");
    DEF(DestineType::Default, "default");

#undef DEF
