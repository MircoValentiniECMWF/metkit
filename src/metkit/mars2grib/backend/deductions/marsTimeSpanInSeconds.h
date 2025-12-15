#pragma once

#include <optional>
#include <array>
#include <string>
#include <string_view>
#include <algorithm>
#include <exception>


#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

// Utils
#include "metkit/mars2grib/utils/timeUtils.h"

// Exceptions
#include "metkit/config/LibMetkit.h"
#include "metkit/mars2grib/utils/mars2grib-exception.h"

namespace metkit::mars2grib::backend::deductions {

template<class MarsDict_t, class ParDict_t>
long marsTimespanInSeconds_or_throw(
    const MarsDict_t& mars, const ParDict_t& par){

    using metkit::mars2grib::utils::dict_traits::get_or_throw;
    using metkit::mars2grib::utils::time::toSeconds_or_throw;
    using metkit::mars2grib::utils::exceptions::Mars2GribDeductionException;

    try {

        // Get the mars.timespan
        std::string marsTimespanVal = get_or_throw<std::string>( mars, "timespan" );

        // Convert to seconds
        long marsTimespanInSecondsVal = toSeconds_or_throw( marsTimespanVal );

        // TODO MIVAL: Validate

        return marsTimespanInSecondsVal;

    } catch ( ... ) {

        // Rethrow nested exceptions
        std::throw_with_nested(
            Mars2GribDeductionException(
                "Unable to get `timespan` from Mars dictionary",
                Here()
            )
        );

    };

    // Remove compiler warning
    __builtin_unreachable();

};

} // namespace metkit::mars2grib::backend::deductions
