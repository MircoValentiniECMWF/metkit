#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "shape_of_the_earth_enum.h"
#include "shape_of_the_earth_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct ShapeOfTheEarthConceptInfo
{
    static constexpr const char* name = "shapeOfTheEarth";

    template<
        int Stage, int Sec,
        ShapeOfTheEarthType Variant,
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
        if constexpr ( shape_of_the_earthApplicable(Stage, Sec, Variant) ) {
            return &ShapeOfTheEarthOp<
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
            shape_of_the_earthTypeName<
                static_cast<ShapeOfTheEarthType>(Variant)
            >()
        );
    }
};
