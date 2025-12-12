#include <array>
#include <utility>
#include <cstdint>

// ======================================================
// Constants
// ======================================================
static constexpr uint8_t NUM_STAGES   = 3;
static constexpr uint8_t NUM_SECTIONS = 6;


// ======================================================
// Prototypes of different capabilities
// ======================================================
template<class MarsDict_t, class GeoDict_t, class ParDict_t, class OptDict_t, class OutDict_t>
using OpFn = uint8_t(*)(const MarsDict_t&, const GeoDict_t&, const ParDict_t&, const OptDict_t&, OutDict_t&);

template<class MarsDict_t, class GeoDict_t, class ParDict_t, class OptDict_t, class OutDict_t>
using CheckFn = bool(*)(const MarsDict_t&, const GeoDict_t&, const ParDict_t&, const OptDict_t&, const OutDict_t&);

template<class OptDict_t, class OutDict_t>
using Grib1ToGrib2Fn = uint8_t(*)(const OutDict_t&, const OutDict_t&, const OutDict_t& );

// ======================================================
// Definition of a capability table
// ======================================================
template<class Fn>
using CapabilityTable =
    std::array<
        std::array<Fn, NSECTIONS>,  // sections
        NSTAGES                     // stages
    >;


// ======================================================
// Prototypes of different capabilities
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
struct Capability
{
    using OpTable =
        CapabilityTable<
            OpFn<MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t>
        >;

    using CheckTable =
        CapabilityTable<
            CheckFn<MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t>
        >;

    using Grib1ToGrib2Table =
        CapabilityTable<
            Grib1ToGrib2Fn<OptDict_t, OutDict_t>
        >;

    const OpTable           op;
    const CheckTable        check;
    const Grib1ToGrib2Table grib1_to_grib2;
};