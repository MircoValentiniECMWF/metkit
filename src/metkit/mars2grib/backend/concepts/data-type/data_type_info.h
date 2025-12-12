#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "data_type_enum.h"
#include "data_type_encoding.h"

namespace metkit::mars2grib::backend {

// ======================================================
// ConceptInfo
// ======================================================
struct DataTypeConceptInfo
{
    static constexpr const char* name = "dataType";

    template<
        int Stage, int Sec,
        DataTypeType Variant,
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
        if constexpr ( data_typeApplicable(Stage, Sec, Variant) ) {
            return &DataTypeOp<
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
            data_typeTypeName<
                static_cast<DataTypeType>(Variant)
            >()
        );
    }
};

} // namespace metkit::mars2grib::backend