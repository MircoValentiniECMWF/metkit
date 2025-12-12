#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "metkit/config/LibMetkit.h"

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/tables/tables_enum.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/tablesVersion.h"
#include "metkit/mars2grib/backend/deductions/localTablesVersion.h"

namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool tablesApplicable(int Stage, int Section, TablesType Variant)
{

    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
      (Variant == TablesType::Default),
      (Stage == StageType::Preset),
      (Section == SectionType::LocalUseSection)
    }};

    // Confitions to apply concept
    return std::all_of(
        conditions.begin(),
        conditions.end(),
        [](bool b){ return b; }
    );
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    TablesType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t TablesOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{

    if constexpr ( tablesApplicable(Stage, Section, Variant) ) {


        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
            << "[Concept Tables] Op called: "
            << "Stage="   << Stage
            << ", Section=" << Section
            << ", Variant=" << std::string(tablesTypeName<Variant>())
            << std::endl;

        // deduce tablesVersion and localTablesVersion
        long tablesVersionVal = deductions::tablesVersion<MarsDict_t,ParDict_t>( mars, par );
        long localTablesVersionVal = deductions::localTablesVersion<MarsDict_t,ParDict_t>( mars, par );

        // set in output dictionary
        set_or_throw<ConceptException>(  out, "tablesVersion",
            tablesVersionVal,
            [&tablesVersionVal](){ return "`tablesVersion` could not be deduced from MARS dictionaries: " +  std::to_string(tablesVersionVal); },
            Here()
        );
        set_or_throw<ConceptException>(  out, "localTablesVersion",
            localTablesVersionVal,
            [&localTablesVersionVal](){ return "`localTablesVersion` could not be deduced from MARS dictionaries: " +  std::to_string(localTablesVersionVal); },
            Here()
        );

        // Successful operation
        return 0;

    }

    // Operation not applicable
    return 1;

}

} // namespace metkit::mars2grib::backend