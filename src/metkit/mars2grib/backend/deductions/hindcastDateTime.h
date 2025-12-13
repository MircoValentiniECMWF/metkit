#pragma once

#include <optional>
#include <array>
#include <string>
#include <string_view>
#include <algorithm>


#include "eckit/types/Date.h"
#include "eckit/types/Time.h"
#include "eckit/types/DateTime.h"
#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

#include "metkit/config/LibMetkit.h"
#include "metkit/mars2grib/utils/mars2grib-exception.h"

namespace metkit::mars2grib::backend::deductions {

template<class MarsDict_t, class ParDict_t>
eckit::DateTime hindcastDateTime(
    const MarsDict_t& mars, const ParDict_t& par){

    using metkit::mars2grib::utils::dict_traits::get_or_throw;
    using metkit::mars2grib::utils::exceptions::Mars2GribDeductionException;

    try {

      // Get the mars.date and mars.time
      auto marsDate = get_or_throw<long>( mars, "hdate" );

      auto marsTime = get_or_throw<long>( mars, "htime" );

      return eckit::DateTime(marsDate, marsTime);

    } catch ( ... ) {

        // Rethrow nested exceptions
        std::throw_with_nested(
            Mars2GribDeductionException(
                "Unable to get `date` and `time` from Mars dictionary to deduce `dateTime`",
                Here()
            )
        );

    };

};

} // namespace metkit::mars2grib::backend::deductions
