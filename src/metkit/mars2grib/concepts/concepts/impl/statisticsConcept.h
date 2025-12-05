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
enum class StatisticsType : int {
    Sincelastpostprocessing = 0,
    Sincebeginningofsimulation = 1,
    Fixedtimerange = 2
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using StatisticsList = ValueList<
    StatisticsType::Sincelastpostprocessing,
    StatisticsType::Sincebeginningofsimulation,
    StatisticsType::Fixedtimerange
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<StatisticsType T>
constexpr std::string_view statisticsTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view statisticsTypeName<T>() { return NAME; }

    DEF(StatisticsType::Sincelastpostprocessing, "SinceLastPostProcessing");
    DEF(StatisticsType::Sincebeginningofsimulation, "SinceBeginningOfSimulation");
    DEF(StatisticsType::Fixedtimerange, "FixedTimerange");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool statisticsApplicable(int Stage, int Section, StatisticsType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    StatisticsType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t StatisticsOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Statistics] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(statisticsTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct StatisticsConceptInfo
{
    static constexpr const char* name = "statistics";

    template<
        int Stage, int Sec,
        StatisticsType Variant,
        class MarsDict_t,
        class GeoDict_t,
        class ParDict_t,
        class OptDict_t,
        class OutDict_t
    >
    static constexpr Fn<
        MarsDict_t,
        GeoDict_t,
        ParDict_t,
        OptDict_t,
        OutDict_t
    > entry()
    {
        if constexpr ( statisticsApplicable(Stage, Sec, Variant) ) {
            return &StatisticsOp<
                Stage, Sec, Variant,
                MarsDict_t,
                GeoDict_t,
                ParDict_t,
                OptDict_t,
                OutDict_t
            >;
        } else {
            return nullptr;
        }
    }

    template<auto Variant>
    static std::string_view variantName()
    {
        return std::string_view(
            statisticsTypeName<
                static_cast<StatisticsType>(Variant)
            >()
        );
    }
};
