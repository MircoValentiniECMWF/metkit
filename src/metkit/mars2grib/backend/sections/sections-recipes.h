#include <optional>
#include <string_view>
#include <initializer_list>
#include <cstdint>
#include <utility>


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


// Section 0 recipes
std::pair<uint16_t, ConceptList> Sec0Recipes[] = {
    { 0,    {{"nil"} } }
};

// Section 1 recipes
std::pair<uint16_t, ConceptList> Sec1Recipes[] = {
    { 0,    {{"origin"}, {"tables"}, {"forecastTime"}, {"dataType"} } }
};

// Section 2 recipes
std::pair<uint16_t, ConceptList> Sec2Recipes[] = {
    { 1,    {{"mars"} } },
    { 15,   {{"mars"}, {"longrange"}} },
    { 24,   {{"mars"}, {"satellite"}} },
    { 36,   {{"mars"}, {"analysis"}} },
    { 1001, {{"mars"}, {"climateDT"}} },
    { 1002, {{"mars"}, {"extremesDT"}} },
    { 1004, {{"mars"}, {"onDemandExtremesDT"}} }
};


// Section 3 recipes
std::pair<uint16_t, ConceptList> Sec3Recipes[] = {
    { 0,   {{"shapeOfTheEarth"}, {"representation", "latlon"}} },
    { 40,  {{"shapeOfTheEarth"}, {"representation", "gaussian"}} }, // Can be regular or reduced
    { 50,  {{"representation", "sphericalHarmonics"}} },
    { 101, {{"shapeOfTheEarth"}, {"representation", "generalUnstructured"}} }, // ORCA grids
    { 150, {{"shapeOfTheEarth"}, {"representation", "healpix"}} }
};

// Section 4 recipes
std::pair<uint16_t, ConceptList> Sec4Recipes[] = {
// Base products
    { 0,   {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"param"} } },             // time point, deterministic
    { 1,   {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"param"}, {"ensemble", "individual"} } }, // time point, ensemble point
    { 2,   {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"param"}, {"ensemble", "derived"} } }, // time point, ensemble statistics
// Base Time statistics
    { 8,   {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"param"} } },             // time statistics, deterministic
    { 11,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"param"}, {"ensemble", "individual"}} }, // time statistics, ensemble point
    { 12,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"param"}, {"ensemble", "derived"}} }, // time statistics, ensemble statistics
// Satellite data
    { 32,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"satellite"}, {"param"} } },
    { 33,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"satellite"}, {"param"}, {"ensemble", "individual"} } },
// Chemical compositions
    { 40,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","chem"},    {"param"} } },
    { 41,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","chem"},    {"param"}, {"ensemble", "individual"} } },
    { 42,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","chem"},    {"param"} } },
    { 43,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","chem"},    {"param"}, {"ensemble", "individual"} } },
// Aerosols properties
    { 50,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","aerosol"}, {"param"} } },
    { 45,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","aerosol"}, {"param"}, {"ensemble", "individual"} } },
    { 46,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","aerosol"}, {"param"} } },
    { 85,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","aerosol"}, {"param"}, {"ensemble", "individual"} } },
// Aerosol/Optical properties
    { 48,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","aerosolOptical"}, {"param"} } },
    { 49,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","aerosolOptical"}, {"param"}, {"ensemble", "individual"} } },
// ?? Reforecast I don't have any idea what these are
    { 60,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"param"}, {"reforecast"}} },
    { 61,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"param"}, {"reforecast"}} },
// Chemical source
    { 76,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","chemicalSource"},    {"param"} } },
    { 77,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","chemicalSource"},    {"param"}, {"ensemble", "individual"} } },
    { 78,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","chemicalSource"},    {"param"} } },
    { 79,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","chemicalSource"},    {"param"}, {"ensemble", "individual"} } },
// Aerosol/Optical source
    { 76,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","aerosolOpticalSource"},    {"param"} } },
    { 77,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"level"},     {"composition","aerosolOpticalSource"},    {"param"}, {"ensemble", "individual"} } },
    { 78,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","aerosolOpticalSource"},    {"param"} } },
    { 79,  {{"generatingProcess"}, {"forecastTime"}, {"statistics"},  {"level"},     {"composition","aerosolOpticalSource"},    {"param"}, {"ensemble", "individual"} } },
// Waves
    { 99,  {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"param"},     {"wave", "Spectra"}} },
    { 100, {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"param"},     {"wave", "Spectra"}, {"ensemble", "individual"} } },
    { 103, {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"param"},     {"wave", "Period"}} },
    { 104, {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"param"},     {"wave", "Period"},  {"ensemble", "individual"} } },
// ??? -> I don't have any idea of what these could be
    { 142, {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"param"},     {"ensemble", "perturbedParameters"} } },
    { 143, {{"generatingProcess"}, {"forecastTime"}, {"pointInTime"}, {"param"},     {"ensemble", "randomPatterns"} } }
};

// Section 1 recipes
std::pair<uint16_t, ConceptList>  Sec5Recipes[] = {
    { 0,  { { "packing", "simple"} } },
    { 42, { { "packing", "ccsds"} } },
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

const std::optional<ConceptList> search(uint16_t sectionId, uint16_t tmpl)
{
    switch(sectionId) {
        case 0: return binarySearch(Sec0Recipes, tmpl);
        case 1: return binarySearch(Sec1Recipes, tmpl);
        case 2: return binarySearch(Sec2Recipes, tmpl);
        case 3: return binarySearch(Sec3Recipes, tmpl);
        case 4: return binarySearch(Sec4Recipes, tmpl);
        default: return std::nullopt;
    }
}
