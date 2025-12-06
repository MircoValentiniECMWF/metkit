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
enum class SatelliteType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using SatelliteList = ValueList<
    SatelliteType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<SatelliteType T>
constexpr std::string_view satelliteTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view satelliteTypeName<T>() { return NAME; }

    DEF(SatelliteType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool satelliteApplicable(int Stage, int Section, SatelliteType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    SatelliteType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t SatelliteOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Satellite] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(satelliteTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct SatelliteConceptInfo
{
    static constexpr const char* name = "satellite";

    template<
        int Stage, int Sec,
        SatelliteType Variant,
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
        if constexpr ( satelliteApplicable(Stage, Sec, Variant) ) {
            return &SatelliteOp<
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
            satelliteTypeName<
                static_cast<SatelliteType>(Variant)
            >()
        );
    }
};
