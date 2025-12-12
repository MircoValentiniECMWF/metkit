#pragma once

#include <string>
#include <exception>

#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

#include "metkit/config/LibMetkit.h"
#include "metkit/mars2grib/utils/mars2grib-exception.h"

namespace metkit::mars2grib::backend::deductions {

template<class MarsDict_t, class ParDict_t>
std::string mars_origin( const MarsDict_t& mars, const ParDict_t& par){

    try {

        // Lookup origin from the mars dictionary
        auto origin = get_or_throw<std::string>( mars, "origin" );


        // Return validated origin
        return origin.value();
    }
    catch ( ... ) {

        // Rethrow nested exceptions
        std::rethrow_with_nested(
            utils::Mars2gGibDeductionException(
                "Unable to get `origin` as string from Mars dictionary",
                Here()
            );
        );
    }

};

} // namespace metkit::mars2grib::backend::deductions
