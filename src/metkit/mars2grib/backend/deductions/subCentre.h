#pragma once

#include <optional>

#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

#include "metkit/config/LibMetkit.h"


namespace metkit::mars2grib::backend::deductions {

template<class MarsDict_t, class ParDict_t>
long sub_centre( const MarsDict_t& mars, const ParDict_t& par ){

    // Stupid deduction rule, but it is what it is for now
    try {

        long subCentre = get<long>( par, "subCentre" ).value_or(0L);

        return subCentre;

    }
    catch ( ... ) {

        // Rethrow nested exceptions
        std::rethrow_with_nested(
            utils::Mars2gGibException(
                "Unable to get `subCentre` as string from Par dictionary",
                Here()
            );
        );
    }

};

} // namespace metkit::mars2grib::backend::deductions