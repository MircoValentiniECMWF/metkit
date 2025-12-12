#pragma once

#include <string>
#include <string_view>
#include <iostream>


// Core concept includes
#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/concepts/time/reference_time_enum.h"

// Deductions
#include "metkit/mars2grib/backend/deductions/significanceOfReferenceTime.h"
#include "metkit/mars2grib/backend/deductions/dateTime.h"
#include "metkit/mars2grib/backend/deductions/referenceDateTime.h"

namespace metkit::mars2grib::backend {

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool timeApplicable(int Stage, int Section, TimeType Variant)
{

    // Compile time conditions to apply this concept
    std::array<bool,3> conditions1 = {{
      (Variant == TimeType::Standard || Variant == TimeType::Reforecast),
      (Stage   == StageType::Preset),
      (Section == SectionType::IdentificationSection)
    }};

    std::array<bool,3> conditions2 = {{
      (Variant == Variant == TimeType::Reforecast),
      (Stage   == StageType::Preset),
      (Section == SectionType::ProductDefinitionSection)
    }};

    // Confitions to apply concept
    return std::all_of(
            conditions1.begin(),
            conditions1.end(),
            [](bool b){ return b; }
        ) ||
        std::all_of(
            conditions2.begin(),
            conditions2.end(),
            [](bool b){ return b; }
        );
}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    ForecastTimeType Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t ForecastTimeOp(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out )
{

    if constexpr ( timeApplicable(Stage, Section, Variant) ) {

        // =============================================================
        // Logging
        LOG_DEBUG_LIB(LibMetkit)
            << "[Concept Time] Op called: "
            << "Stage="   << Stage
            << ", Section=" << Section
            << ", Variant=" << std::string(timeTypeName<Variant>())
            << std::endl;

        // =============================================================
        //

        // Deduce date and time components from dateTime deduction
        if ( auto dateTime = deductions::dateTime<MarsDict_t,ParDict_t>( mars, par ); !dateTime.has_value() ){
            throw ConceptException(
                "`date/time` is mandatory and could not be deduced from MARS dictionaries",
                Here()
            );
        }

        if constexpr ( Section == SectionType::IdentificationSection ) {

            // Significance of reference time is always deduced the same way
            if ( auto significanceOfReferenceTimeOpt = deductions::significanceOfReferenceTime<MarsDict_t,ParDict_t>( mars, par ); significanceOfReferenceTimeOpt.has_value() ){
                set_or_throw<ConceptException>(  out, "significanceOfReferenceTime",
                    long(significanceOfReferenceTimeOpt.value()),
                    [&significanceOfReferenceTimeOpt](){ return "`significanceOfReferenceTime` could not be deduced from MARS dictionaries: " + std::to_string(long(significanceOfReferenceTimeOpt.value())); },
                    Here()
                );
            }
            else {
                throw ConceptException(
                    "`significanceOfReferenceTime` is mandatory and could not be deduced from MARS dictionaries",
                    Here()
                );
            }


            // =============================================================
            if constexpr ( Variant == TimeType::Standard ) {

                // Set date and time components in output dictionary
                set_or_throw<ConceptException,long>( out, "year",
                    dateTime.date().year(),
                    [](){ return "`year` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "month",
                    dateTime.date().month(),
                    [](){ return "`month` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "day",
                    dateTime.date().day(),
                    [](){ return "`day` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "hour",
                    DateTime.time().hours(),
                    [](){ return "`hour` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "minute",
                    DateTime.time().minutes(),
                    [](){ return "`minute` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "second",
                    DateTime.time().seconds(),
                    [](){ return "`second` could not be deduced from MARS dictionaries"; },
                    Here()
                );

            }

            if constexpr ( Variant == TimeType::Reforecast ) {

                // Deduce date and time components from dateTime deduction
                if ( auto referenceDateTime = deductions::referenceDateTime<MarsDict_t,ParDict_t>( mars, par ); !referenceDateTime.has_value() ){
                    throw ConceptException(
                        "`dateTime` is mandatory and could not be deduced from MARS dictionaries",
                        Here()
                    );
                }

                //
                // Set date and time components in output dictionary
                set_or_throw<ConceptException,long>( out, "year",
                    referenceDateTime.date().year(),
                    [](){ return "`year` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "month",
                    referenceDateTime.date().month(),
                    [](){ return "`month` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "day",
                    referenceDateTime.date().day(),
                    [](){ return "`day` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "hour",
                    referenceDateTime.time().hours(),
                    [](){ return "`hour` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "minute",
                    referenceDateTime.time().minutes(),
                    [](){ return "`minute` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "second",
                    referenceDateTime.time().seconds(),
                    [](){ return "`second` could not be deduced from MARS dictionaries"; },
                    Here()
                );
            } // if constexpr ( Variant == TimeType::Reforecast )
        } // if constexpr ( Section == SectionType::IdentificationSection )



        if constexpr ( Section == SectionType::ProductDefinitionSection ) {
            if constexpr ( Variant == TimeType::Reforecast ) {

                check_or_throw<long,ConceptException>( out, "ProductDefinitionTemplateNumber",
                    []( long& v ){
                        if ( v != 60 && v != 61 ) {
                            throw ConceptException("localDefinitionNumber is not one of [60,61] hence not associated to a reforecast product", Here());
                        };
                        return true;
                    }
                );

                //
                // Set date and time components in output dictionary
                set_or_throw<ConceptException,long>( out, "YearOfModelVersion",
                    dateTime.date().year(),
                    [](){ return "`year` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "MonthOfModelVersion",
                    dateTime.date().month(),
                    [](){ return "`month` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "DayOfModelVersion",
                    dateTime.date().day(),
                    [](){ return "`day` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "HourOfModelVersion",
                    dateTime.time().hours(),
                    [](){ return "`hour` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "MinuteOfModelVersion",
                    dateTime.time().minutes(),
                    [](){ return "`minute` could not be deduced from MARS dictionaries"; },
                    Here()
                );
                set_or_throw<ConceptException,long>( out, "SecondOfModelVersion",
                    dateTime.time().seconds(),
                    [](){ return "`second` could not be deduced from MARS dictionaries"; },
                    Here()
                );
            }; // if constexpr ( Variant == TimeType::Standard )
        } // if constexpr ( Section == SectionType::ProductDefinitionSection  )


        // Successful operation
        return 0;

    } // if constexpr ( timeApplicable(Stage, Section, Variant) ) {

    // Operation not applicable
    return 1;
}

}  // namespace metkit::mars2grib::backend
