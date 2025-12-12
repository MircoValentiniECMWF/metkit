#pragma once

#include <optional>

#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

#include "metkit/config/LibMetkit.h"


namespace metkit::mars2grib::backend::deductions {

// grib2 section 2.36 for analysis fields. octets 19-20
template<class MarsDict_t, class ParDict_t>
std::optional<long> lengthOfTimeWindow(
    const MarsDict_t& mars, const ParDict_t& par){

        // Stupid deduction rule, but it is what it is for now
        return get<long>( par, "lengthOfTimeWindow" );

    };

} // namespace metkit::mars2grib::backend::deductions