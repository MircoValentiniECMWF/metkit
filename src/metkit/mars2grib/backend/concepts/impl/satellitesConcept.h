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
enum class SatellitesType : int {
    Default = 0
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using SatellitesList = ValueList<
    SatellitesType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<SatellitesType T>
constexpr std::string_view satellitesTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view satellitesTypeName<T>() { return NAME; }

    DEF(SatellitesType::Default, "default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool satellitesApplicable(int Stage, int Section, SatellitesType Variant)
{
    return false;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    SatellitesType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t SatellitesOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Satellites] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(satellitesTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct SatellitesConceptInfo
{
    static constexpr const char* name = "satellites";

    template<
        int Stage, int Sec,
        SatellitesType Variant,
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
        if constexpr ( satellitesApplicable(Stage, Sec, Variant) ) {
            return &SatellitesOp<
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
            satellitesTypeName<
                static_cast<SatellitesType>(Variant)
            >()
        );
    }
};
