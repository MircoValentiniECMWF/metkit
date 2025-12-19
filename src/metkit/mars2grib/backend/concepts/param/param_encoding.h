#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <array>
#include <exception>

// dictionary traits
#include "metkit/mars2grib/utils/dictionary_traits/dictionary_access_traits.h"

// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/param/param_enum.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/paramId.h"

// Exceptions
#include "metkit/mars2grib/utils/mars2grib-exception.h"

namespace metkit::mars2grib::backend::cnpts {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
template<
    std::size_t Stage,
    std::size_t Section,
    ParamType Variant
>
constexpr bool paramApplicable()
{

    // Confitions to apply concept
    return ((Variant == ParamType::ParamId) &&
            (Stage == StagePreset || Stage == StageRuntime) &&
            (Section == SecProductDefinitionSection));
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    std::size_t Stage,
    std::size_t Section,
    ParamType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
void ParamOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{
    using metkit::mars2grib::utils::dict_traits::get_opt;
    using metkit::mars2grib::utils::dict_traits::get_or_throw;
    using metkit::mars2grib::utils::dict_traits::set_or_throw;
    using metkit::mars2grib::utils::exceptions::Mars2GribConceptException;

    if constexpr ( paramApplicable<Stage, Section, Variant>() ) {

        try {

            // Debug output
            LOG_DEBUG_LIB(LibMetkit)
                << "[Concept Param] Op called: "
                << "Stage="   << Stage
                << ", Section=" << Section
                << ", Variant=" << std::string(paramTypeName<Variant>())
                << std::endl;

            // Deduction rules
            long paramId = deductions::paramId( mars, par );


            // DEBUG CODE
            // long PDT = get_or_throw<long>( out, "productDefinitionTemplateNumber" );
            // long NTR = get_opt<long>( out, "numberOfTimeRange" ).value_or(-1);
            // std::string TOL = get_or_throw<std::string>( out, "typeOfLevel" );
            // long lev = get_or_throw<long>( out, "level" );

            // if ( paramId == 237167 ){
            //     set_or_throw<long>( out, "typeOfFirstFixedSurface", 103 );
            // }


            // Check type Of level
            // auto l00 = get_opt<long>( out, "typeOfFirstFixedSurface" ).value_or(-1);
            // auto l01 = get_opt<long>( out, "typeOfSecondFixedSurface" ).value_or(-1);
            // auto l02 = get_opt<int>( out, "scaledValueOfFirstFixedSurface" ).value_or(-1);
            // auto l10 = get_opt<int>( out, "scaledValueOfSecondFixedSurface" ).value_or(-1);
            // auto l11 = get_opt<int>( out, "scaleFactorOfFirstFixedSurface" ).value_or(-1);
            // auto l12 = get_opt<int>( out, "scaleFactorOfSecondFixedSurface" ).value_or(-1);

            // std::cout << "PDT: " << PDT << ", " << NTR << ", " << TOL << ", " << lev <<
            // ", " << l00 << ", " << l01 << ", " << l02 << ", " << l10 << ", " << l11 << ", " << l12 << std::endl;

            // Set values in output dictionary (grib sample)
            set_or_throw<long>( out, "paramId", paramId );

        }
        catch ( ... ) {
            // Rethrow nested exceptions
            std::throw_with_nested(
                Mars2GribConceptException(
                    std::string( paramName ),
                    std::string( paramTypeName<Variant>() ),
                    std::to_string(Stage),
                    std::to_string(Section),
                    "Unable to set `param` concept...",
                    Here()
                )
            );
        }

        // Successful operation
        return;

    } // if constexpr ( originApplicable(Stage, Section, Variant) )

    // Paranoid check. Should never arrive here
    throw Mars2GribConceptException(
            std::string( paramName ),
            std::string( paramTypeName<Variant>() ),
            std::to_string(Stage),
            std::to_string(Section),
            "Concept called when not applicable...",
            Here()
        );

    // Remove compiler warning
    __builtin_unreachable();

}

}