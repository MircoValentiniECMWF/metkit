#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <array>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/data-type/data_type_enum.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/typeOfProcessed.h"
#include "metkit/mars2grib/backend/deductions/productionStatusOfProcessedData.h"

namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool data_typeApplicable(int Stage, int Section, DataTypeType Variant)
{
    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
        (Variant == DataTypeType::Default),
        (Stage == StageType::Preset),
        (Section == SectionType::IdentificationSection)
    }};

    // Confitions to apply concept
    return std::all_of(
        conditions.begin(),
        conditions.end(),
        [](bool b){ return b; }
    );

    return true;
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    DataTypeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t DataTypeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{


    if constexpr ( data_typeApplicable(Stage, Section, Variant) ) {

        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
              << "[Concept DataType] Op called: "
              << "Stage="     << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string(data_typeTypeName<Variant>())
              << std::endl;

        // Lookup needed data
        if ( auto typeOfProcessedDataOpt = deductions::typeOfProcessedData<MarsDict_t,ParDict_t>( mars, par ); typeOfProcessedDataOpt.has_value() ){
            set_or_throw<ConceptException>(  out, "typeOfProcessedData",
                long(typeOfProcessedDataOpt.value()),
                [&typeOfProcessedDataOpt](){ return "`typeOfProcessedData` could not be deduced from MARS dictionaries: " + std::to_string(typeOfProcessedDataOpt.value()); },
                Here()
            );
        }
        else {
            throw ConceptException(
                "`typeOfProcessedData` is mandatory and could not be deduced from MARS dictionaries",
                Here()
            );
        }

        // TODO MIVAL: In the fortran code this is not set if missing, need to clarify with DGOV team
        if ( auto productionStatusOfProcessedDataOpt = deductions::productionStatusOfProcessed<MarsDict_t,ParDict_t>( mars, par ); productionStatusOfProcessedDataOpt.has_value() ) {
            set_or_throw<ConceptException>(  out, "productionStatusOfProcessedData",
                long(productionStatusOfProcessedDataOpt.value()),
                [&productionStatusOfProcessedDataOpt](){ return "`productionStatusOfProcessedData` could not be deduced from MARS dictionaries: " + std::to_string(productionStatusOfProcessedDataOpt.value()); },
                Here()
            );
        }
        else {
            LOG_DEBUG_LIB(LibMetkit)
                << "`productionStatusOfProcessedData` is not set to any value; encoding rely on previous value in the grib header"
                <<  ", at: " << Here()
                << std::endl;
        }

        // Successful operation
        return 0;
    }

    // Operation not applicable
    return 1;
}

}  // namespace metkit::mars2grib::backend