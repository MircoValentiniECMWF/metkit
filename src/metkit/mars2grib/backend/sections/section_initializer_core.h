#pragma once

#include <cstddef>
#include <utility>

namespace metkit::mars2grib::backend::sections {

// ======================================================
// Function pointer type
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
using Fn = void(*)(const MarsDict_t&, const GeoDict_t&, const ParDict_t&, const OptDict_t&, OutDict_t&);

// ======================================================
// Registry entry: (TemplateNumber, Fn)
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
using Entry = std::pair<std::size_t, Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>>;

// ======================================================
// Forward declaration of allocator
// ======================================================
template<
    std::size_t Section,
    std::size_t TemplateNumber,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
void allocateTemplateNumber(const MarsDict_t&, const GeoDict_t&, const ParDict_t&, const OptDict_t&, OutDict_t&);

} // namespace