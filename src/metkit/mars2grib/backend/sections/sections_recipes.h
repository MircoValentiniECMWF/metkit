#pragma once

#include <optional>
#include <string_view>
#include <initializer_list>
#include <cstdint>
#include <utility>

namespace metkit::mars2grib::backend::sections {

struct ConceptSpec {
    std::string_view name;
    std::optional<std::string_view> type;

    // One-argument type = nullopt
    constexpr ConceptSpec(std::string_view n)
        : name(n), type(std::nullopt) {}

    // Two-argument explicit type
    constexpr ConceptSpec(std::string_view n, std::string_view t)
        : name(n), type(t) {}
};

using ConceptList = std::initializer_list<ConceptSpec>;


// ===================================================================================================================
// Section 0 recipes
std::pair<uint16_t, ConceptList> Sec0Recipes[] = {
    { 0,    {{"nil"} } }
};


// ===================================================================================================================
// Section 1 recipes
std::pair<uint16_t, ConceptList> Sec1Recipes[] = {
    { 0,    {{"origin"}, {"tables"}, {"referenceTime"}, {"dataType"} } }
};


// ===================================================================================================================
// Section 2 recipes
std::pair<uint16_t, ConceptList> Sec2Recipes[] = {
    { 1,    {{"mars"} } },
    { 15,   {{"mars"}, {"longrange"}} },
    { 24,   {{"mars"}, {"satellite"}} },
    { 36,   {{"mars"}, {"analysis"}} },
    { 1001, {{"mars"}, {"destine","climateDT"}} },
    { 1002, {{"mars"}, {"destine","extremesDT"}} },
    { 1004, {{"mars"}, {"destine","onDemandExtremesDT"}} }
};


// ===================================================================================================================
// Section 3 recipes
std::pair<uint16_t, ConceptList> Sec3Recipes[] = {
    // TEMPLATE 3.0, Latitude/longitude (or equidistant cylindrical, or Plate Carree)
    { 0,   {{"shapeOfTheEarth"}, {"representation", "latlon"}} },
    // TEMPLATE 3.40, Gaussian latitude/longitude
    { 40,  {{"shapeOfTheEarth"}, {"representation", "gaussian"}} },
    // TEMPLATE 3.50, Spherical harmonic coefficients
    { 50,  {{"representation", "sphericalHarmonics"}} },
    //  TEMPLATE 3.101, General Unstructured Grid
    { 101, {{"shapeOfTheEarth"}, {"representation", "generalUnstructured"}} },
    // TEMPLATE 3.150, Hierarchical Equal Area isoLatitude Pixelization grid (HEALPix)
    { 150, {{"shapeOfTheEarth"}, {"representation", "healpix"}} }
};

// ===================================================================================================================
// Section 4 recipes
std::pair<uint16_t, ConceptList> Sec4Recipes[] = {
//
// Base products
    // TEMPLATE 4.0, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time
    { 0,   {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"param"} } },
    // TEMPLATE 4.1, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time
    { 1,   {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"param"}, {"ensemble"} } },
    // TEMPLATE 4.2, Derived forecast based on all ensemble members at a horizontal level or in a horizontal layer at a point in time
    { 2,   {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"param"}, {"derived"} } },
//
// Base Time statistics
    // TEMPLATE 4.8, Average, accumulation, and/or extreme values or other statistically processed values at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval
    { 8,   {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"param"} } },
    // TEMPLATE 4.11, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval
    { 11,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"param"}, {"ensemble"}} },
    // TEMPLATE 4.12, Derived forecasts based on all ensemble members at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval
    { 12,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"param"}, {"derived"}} },
//
// Satellite data
    // TEMPLATE 4.32, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for simulated (synthetic) satellite data
    { 32,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"satellite"}, {"param"} } },
    // TEMPLATE 4.33, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for simulated (synthetic) satellite data
    { 33,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"satellite"}, {"param"}, {"ensemble"} } },
//
// Chemical compositions
    // TEMPLATE 4.40, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for atmospheric chemical constituents
    { 40,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"composition","chem"},    {"param"} } },
    // TEMPLATE 4.41, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for atmospheric chemical constituents
    { 41,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"composition","chem"},    {"param"}, {"ensemble"} } },
    // TEMPLATE 4.42, Average, accumulation and/or extreme values or other statistically processed values at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval for atmospheric chemical constituents
    { 42,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"composition","chem"},    {"param"} } },
    // TEMPLATE 4.43, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval for atmospheric chemical constituents
    { 43,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"composition","chem"},    {"param"}, {"ensemble"} } },
//
// Aerosols properties
    // TEMPLATE 4.50, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for aerosol
    { 50,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"composition","aerosol"}, {"param"} } },
    // TEMPLATE 4.45, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for aerosol
    { 45,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"composition","aerosol"}, {"param"}, {"ensemble"} } },
    // TEMPLATE 4.46, Average, accumulation, and/or extreme values or other statistically processed values at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval for aerosol
    { 46,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"composition","aerosol"}, {"param"} } },
    // TEMPLATE 4.85, individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval for aerosol
    { 85,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"composition","aerosol"}, {"param"}, {"ensemble"} } },
//
// Aerosol/Optical properties
    // TEMPLATE 4.48, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for optical properties of aerosol
    { 48,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"composition","aerosolOptical"}, {"param"} } },
    // TEMPLATE 4.49, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for optical properties of aerosol
    { 49,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"composition","aerosolOptical"}, {"param"}, {"ensemble"} } },
//
// ?? Reforecast I don't have any idea what these are
    // TEMPLATE 4.60, Individual ensemble re-forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time
    { 60,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"param"}, {"reforecast"}} },
    // TEMPLATE 4.61, Individual ensemble re-forecast, control and perturbed, at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval
    { 61,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"param"}, {"reforecast"}} },
//
// Chemical source
    // TEMPLATE 4.76, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for atmospheric chemical constituents with source/sink
    { 76,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"composition","chemicalSource"},    {"param"} } },
    // TEMPLATE 4.77, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for atmospheric chemical constituents with a source/sink
    { 77,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"level"},     {"composition","chemicalSource"},    {"param"}, {"ensemble"} } },
    // TEMPLATE 4.78, Average, accumulation and/or extreme values or other statistically processed values at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval for atmospheric chemical constituents with source/sink
    { 78,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"composition","chemicalSource"},    {"param"} } },
    //  TEMPLATE 4.79, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval for atmospheric chemical constituents with source/sink
    { 79,  {{"generatingProcess"}, {"referenceTime"}, {"statistics"},  {"level"},     {"composition","chemicalSource"},    {"param"}, {"ensemble"} } },
//
// Waves
    // TEMPLATE 4.99, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for wave 2D spectra with explicit list of frequencies and directions
    { 99,  {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"param"},     {"wave", "Spectra"}} },
    // TEMPLATE 4.100, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for wave 2D spectra with explicit list of frequencies and directions
    { 100, {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"param"},     {"wave", "Spectra"}, {"ensemble"} } },
    // TEMPLATE 4.103, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for waves selected by period range.
    { 103, {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"param"},     {"wave", "Period"}} },
    // TEMPLATE 4.104, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for waves selected by period range.
    { 104, {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"param"},     {"wave", "Period"},  {"ensemble"} } },
//
// ??? -> I don't have any idea of what these could be
    // TEMPLATE 4.142, Individual ensemble reforecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for wave 2D spectra with explicit list of frequencies and directions
    { 142, {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"param"},     {"ensemble", "perturbedParameters"} } },
    // TEMPLATE 4.143, Random fields used in an ensemble forecast, at a horizontal level or in a horizontal layer at a point in time
    { 143, {{"generatingProcess"}, {"referenceTime"}, {"pointInTime"}, {"param"},     {"ensemble", "randomPatterns"} } }
};


// ===================================================================================================================
// Section 5 recipes
std::pair<uint16_t, ConceptList>  Sec5Recipes[] = {
    // TEMPLATE 5.0, Grid point data - simple packing
    { 0,  { { "packing", "simple"} } },
    // TEMPLATE 5.42, Grid point data - CCSDS recommended lossless compression
    { 42, { { "packing", "ccsds"} } },
    // TEMPLATE 5.51, Spherical harmonics data - complex packing
    { 51, { { "packing", "spectral_complex"} } }
};



template<class Array>
const std::optional<ConceptList> binarySearch(const Array& arr, uint16_t key)
{
    int L = 0;
    int R = (int)(std::size(arr)) - 1;

    while (L <= R) {
        int M = (L + R) / 2;

        auto midKey = arr[M].first;
        if (midKey == key) return std::optional<ConceptList>(arr[M].second);
        if (midKey < key)  L = M + 1;
        else               R = M - 1;
    }
    return std::nullopt;
}

const std::optional<ConceptList> resolveSectionTemplateConcepts(uint16_t sectionId, uint16_t tmpl)
{
    switch(sectionId) {
        case 0: return binarySearch(Sec0Recipes, tmpl);
        case 1: return binarySearch(Sec1Recipes, tmpl);
        case 2: return binarySearch(Sec2Recipes, tmpl);
        case 3: return binarySearch(Sec3Recipes, tmpl);
        case 4: return binarySearch(Sec4Recipes, tmpl);
        case 5: return binarySearch(Sec5Recipes, tmpl);
        default: return std::nullopt;
    }
}

} // namespace metkit::mars2grib::sections