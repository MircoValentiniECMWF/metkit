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

namespace metkit::mars2grib::backend::deductions {

template<class MarsDict_t, class ParDict_t>
eckit::DateTime dateTime(
    const MarsDict_t& mars, const ParDict_t& par){

    // Get the mars.date and mars.time
    auto marsDate = get_or_throw<ConceptException,long>(
        mars, "date",
        [](){
            return "`date` is required in mars dictionary to deduce `date`";
        },
        Here() );

    auto marsTime = get_or_throw<ConceptException,long>(
        mars, "time",
        [](){
            return "`time` is required in mars dictionary to deduce `time`";
        },
        Here() );

    return eckit::DateTime(marsDate, marsTime);

    };

} // namespace metkit::mars2grib::backend::deductions
