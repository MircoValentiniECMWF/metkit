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
enum class LevelType : int {
    Surface = 0,
    Entireatmosphere = 1,
    Entirelake = 2,
    Cloudbase = 3,
    Tropopause = 4,
    Nominaltop = 5,
    Mostunstableparcel = 6,
    Mixedlayerparcel = 7,
    Isothermal = 8,
    Isobaricinpa = 9,
    Isobaricinhpa = 10,
    Lowcloudlayer = 11,
    Mediumcloudlayer = 12,
    Highcloudlayer = 13,
    Meansea = 14,
    Heightabovesea = 15,
    Heightaboveground = 16,
    Hybrid = 17,
    Theta = 18,
    Potentialvorticity = 19,
    Snowlayer = 20,
    Soillayer = 21,
    Seaicelayer = 22,
    Depthbelowsealayer = 23,
    Lakebottom = 24,
    Mixinglayer = 25,
    Icetoponwater = 26,
    Icelayeronwater = 27,
    Abstractsinglelevel = 28,
    Abstractmultiplelevel = 29,
    Heightaboveseaat10m = 30,
    Heightaboveseaat2m = 31,
    Heightabovegroundat10m = 32,
    Heightabovegroundat2m = 33,
    Default = 34
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using LevelList = ValueList<
    LevelType::Surface,
    LevelType::Entireatmosphere,
    LevelType::Entirelake,
    LevelType::Cloudbase,
    LevelType::Tropopause,
    LevelType::Nominaltop,
    LevelType::Mostunstableparcel,
    LevelType::Mixedlayerparcel,
    LevelType::Isothermal,
    LevelType::Isobaricinpa,
    LevelType::Isobaricinhpa,
    LevelType::Lowcloudlayer,
    LevelType::Mediumcloudlayer,
    LevelType::Highcloudlayer,
    LevelType::Meansea,
    LevelType::Heightabovesea,
    LevelType::Heightaboveground,
    LevelType::Hybrid,
    LevelType::Theta,
    LevelType::Potentialvorticity,
    LevelType::Snowlayer,
    LevelType::Soillayer,
    LevelType::Seaicelayer,
    LevelType::Depthbelowsealayer,
    LevelType::Lakebottom,
    LevelType::Mixinglayer,
    LevelType::Icetoponwater,
    LevelType::Icelayeronwater,
    LevelType::Abstractsinglelevel,
    LevelType::Abstractmultiplelevel,
    LevelType::Heightaboveseaat10m,
    LevelType::Heightaboveseaat2m,
    LevelType::Heightabovegroundat10m,
    LevelType::Heightabovegroundat2m,
    LevelType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<LevelType T>
constexpr std::string_view levelTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view levelTypeName<T>() { return NAME; }

    DEF(LevelType::Surface, "Surface");
    DEF(LevelType::Entireatmosphere, "EntireAtmosphere");
    DEF(LevelType::Entirelake, "EntireLake");
    DEF(LevelType::Cloudbase, "CloudBase");
    DEF(LevelType::Tropopause, "Tropopause");
    DEF(LevelType::Nominaltop, "NominalTop");
    DEF(LevelType::Mostunstableparcel, "MostUnstableParcel");
    DEF(LevelType::Mixedlayerparcel, "MixedLayerParcel");
    DEF(LevelType::Isothermal, "Isothermal");
    DEF(LevelType::Isobaricinpa, "IsobaricInPa");
    DEF(LevelType::Isobaricinhpa, "IsobaricInHpa");
    DEF(LevelType::Lowcloudlayer, "LowCloudLayer");
    DEF(LevelType::Mediumcloudlayer, "MediumCloudLayer");
    DEF(LevelType::Highcloudlayer, "HighCloudLayer");
    DEF(LevelType::Meansea, "MeanSea");
    DEF(LevelType::Heightabovesea, "HeightAboveSea");
    DEF(LevelType::Heightaboveground, "HeightAboveGround");
    DEF(LevelType::Hybrid, "Hybrid");
    DEF(LevelType::Theta, "Theta");
    DEF(LevelType::Potentialvorticity, "PotentialVorticity");
    DEF(LevelType::Snowlayer, "SnowLayer");
    DEF(LevelType::Soillayer, "SoilLayer");
    DEF(LevelType::Seaicelayer, "SeaIceLayer");
    DEF(LevelType::Depthbelowsealayer, "DepthBelowSeaLayer");
    DEF(LevelType::Lakebottom, "LakeBottom");
    DEF(LevelType::Mixinglayer, "MixingLayer");
    DEF(LevelType::Icetoponwater, "IceTopOnWater");
    DEF(LevelType::Icelayeronwater, "IceLayerOnWater");
    DEF(LevelType::Abstractsinglelevel, "AbstractSingleLevel");
    DEF(LevelType::Abstractmultiplelevel, "AbstractMultipleLevel");
    DEF(LevelType::Heightaboveseaat10m, "HeightAboveSeaAt10m");
    DEF(LevelType::Heightaboveseaat2m, "HeightAboveSeaAt2m");
    DEF(LevelType::Heightabovegroundat10m, "HeightAboveGroundAt10m");
    DEF(LevelType::Heightabovegroundat2m, "HeightAboveGroundAt2m");
    DEF(LevelType::Default, "Default");

#undef DEF

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool levelApplicable(int Stage, int Section, LevelType Variant)
{
    if (Section != 4)
        return false;

    if (Stage == 0)
        return (Variant == LevelType::Hybrid); // only hybrid needs to allocate something

    return (Stage == 1 || Stage == 2);
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    LevelType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t LevelOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    std::cout << "[Concept Level] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(levelTypeName<Variant>())
              << std::endl;
    return 0;
}

// ======================================================
// ConceptInfo
// ======================================================
struct LevelConceptInfo
{
    static constexpr const char* name = "level";

    template<
        int Stage, int Sec,
        LevelType Variant,
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
        if constexpr ( levelApplicable(Stage, Sec, Variant) ) {
            return &LevelOp<
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
    static std::string variantName()
    {
        return std::string(
            levelTypeName<
                static_cast<LevelType>(Variant)
            >()
        );
    }
};
