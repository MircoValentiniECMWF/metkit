#pragma once

#include <optional>
#include <array>
#include <string>
#include <string_view>
#include <algorithm>

#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

#include "metkit/config/LibMetkit.h"

namespace metkit::mars2grib::backend::deductions {

template<class MarsDict_t, class ParDict_t>
long tablesVersion( const MarsDict_t& mars, const ParDict_t& par){

    try {

        // Get the mars.date and mars.time
        return metkit::codes::codesHandleFromSample("GRIB2")->getLong("tablesVersionLatest");

    }
    catch ( ... ){
        std::throw_with_nested(
            eckit::ConceptException(
                "Could not deduce `tablesVersion` from GRIB2 sample",
                Here()
            )
        );
    }

    };

} // namespace metkit::mars2grib::backend::deductions
