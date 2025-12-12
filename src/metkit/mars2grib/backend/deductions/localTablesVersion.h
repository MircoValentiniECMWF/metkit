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
long localTablesVersion( const MarsDict_t& mars, const ParDict_t& par){

    return 0L;

};

} // namespace metkit::mars2grib::backend::deductions
