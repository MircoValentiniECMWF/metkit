#pragma once

#include <optional>
#include <cstdint>

#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

#include "metkit/config/LibMetkit.h"


namespace metkit::mars2grib::backend::deductions {


template<class MarsDict_t, class ParDict_t>
tlong numberOfForecastsInEnsemble(
    const MarsDict_t& mars, cost ParDict_t& par){

    // The only way to infer this is from parametrization
    return get_or_throw<ConceptException,long>( par, "numberOfForecastsInEnsemble",
        [](){
            return "`numberOfForecastsInEnsemble` is required in mars dictionary to deduce `numberOfForecastsInEnsemble`";
        },
        Here()
    );

};


} // namespace metkit::mars2grib::backend::deductions