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
enum class RepresentationType : int {
    Latlon = 0,
    Gaussian,
    SphericalHarmonics,
    GeneralUnstructured,
    Healpix,
    Orca,
    Fesom,
    Default
};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using RepresentationList = ValueList<
    RepresentationType::Latlon,
    RepresentationType::Gaussian,
    RepresentationType::SphericalHarmonics,
    RepresentationType::GeneralUnstructured,
    RepresentationType::Healpix,
    RepresentationType::Orca,
    RepresentationType::Fesom,
    RepresentationType::Default
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<RepresentationType T>
constexpr std::string_view representationTypeName();

#define DEF(T,NAME) \
    template<> constexpr std::string_view representationTypeName<T>() { return NAME; }

    DEF(RepresentationType::Latlon, "latlon");
    DEF(RepresentationType::Gaussian, "gaussian");
    DEF(RepresentationType::SphericalHarmonics, "sphericalHarmonics");
    DEF(RepresentationType::GeneralUnstructured, "generalUnstructured");
    DEF(RepresentationType::Healpix, "healpix");
    DEF(RepresentationType::Orca, "orca");
    DEF(RepresentationType::Fesom, "fesom");
    DEF(RepresentationType::Default, "default");

#undef DEF
