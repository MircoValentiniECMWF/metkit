#pragma once

#include <string>
#include <string_view>
#include <iostream>

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/ensemble/ensemble_enum.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/typeOfEnsembleForecast.h"
#include "metkit/mars2grib/backend/deductions/numberOfForecastsInEnsemble.h"

namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool ensembleApplicable(int Stage, int Section, EnsembleType Variant)
{
    // Compile time conditions to apply this concept
    std::array<bool,3> conditions = {{
      (Variant == EnsembleType::Individual),
      (Stage == StageType::Preset),
      (Section == SectionType::ProductDefinitionSection)
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
    EnsembleType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t EnsembleOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{

    if constexpr ( ensembleApplicable(Stage, Section, Variant) ) {


        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
            << "[Concept Ensemble] Op called: "
            << "Stage="   << Stage
            << ", Section=" << Section
            << ", Variant=" << std::string(ensembleTypeName<Variant>())
            << std::endl;

        // =============================================================
        // Deduce typeOfEnsembleForecast from mars dictionary
        auto typeOfEnsembleForecast = deductions::typeOfEnsembleForecast( mars, par );
        auto numberOfForecastsInEnsemble = deductions::numberOfForecastsInEnsemble( mars, par );


        // Set grib key
        set_or_throw<ConceptException>( out, "typeOfEnsembleForecast",
                long(typeOfEnsembleForecast),
                [&typeOfEnsembleForecast](){ return "`typeOfEnsembleForecast` could not be set to the grib header with value: " + std::to_string(long(typeOfEnsembleForecast)); },
                Here()
            );

        set_or_throw<ConceptException>( out, "numberOfForecastsInEnsemble",
                long(numberOfForecastsInEnsemble),
                [&numberOfForecastsInEnsemble](){ return "`numberOfForecastsInEnsemble` could not be set to the grib header with value: " + std::to_string(long(numberOfForecastsInEnsemble)); },
                Here()
            );


        // Successful operation
        return 0;

    }

    // Operation not applicable
    return 1;

}

} // namespace metkit::mars2grib::backend