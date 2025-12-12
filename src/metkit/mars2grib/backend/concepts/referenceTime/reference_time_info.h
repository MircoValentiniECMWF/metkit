#pragma once

#include <string>
#include <string_view>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"

#include "metkit/mars2grib/backend/concepts/time/reference_time_enum.h"
#include "metkit/mars2grib/backend/concepts/time/reference_time_encoding.h"

namespace metkit::mars2grib::backend {

// ======================================================
// ConceptInfo
// ======================================================
struct TimeConceptInfo
{
    static constexpr const char* name = "time";

    template<
        int Stage, int Sec,
        TimeType Variant,
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
        if constexpr ( timeApplicable(Stage, Sec, Variant) ) {
            return &TimeOp<
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

        // Remove compiler warning
        return nullptr;
    }

    template<auto Variant>
    static std::string_view variantName()
    {
        return std::string_view(
            timeTypeName<
                static_cast<TimeType>(Variant)
            >()
        );
    }
};

} // namespace metkit::mars2grib::backend