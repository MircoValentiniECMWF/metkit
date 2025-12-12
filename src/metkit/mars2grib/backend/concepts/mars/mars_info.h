#pragma once

#include <string>
#include <string_view>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/mars/mars_enum.h"
#include "metkit/mars2grib/backend/concepts/mars/mars_encoding.h"

namespace metkit::mars2grib::backend {

// ======================================================
// ConceptInfo
// ======================================================
struct MarsConceptInfo
{
    static constexpr const char* name = "mars";

    template<
        int Stage, int Sec,
        MarsType Variant,
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
        if constexpr ( marsApplicable(Stage, Sec, Variant) ) {
            return &MarsOp<
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
            marsTypeName<
                static_cast<MarsType>(Variant)
            >()
        );
    }
};

} // namespace metkit::mars2grib::backend