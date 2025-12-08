#pragma once

#include "metkit/mars2grib/backend/GenericFrozenEncoder.h"

#include <eckit/config/LocalConfiguration.h>
#include <metkit/codes/api/CodesAPI.h>

namespace metkit::mars2grib::backend {

using LocalConfigurationFrozenEncoder =
    GenericFrozenEncoder<
        eckit::LocalConfiguration,
        eckit::LocalConfiguration,
        eckit::LocalConfiguration,
        eckit::LocalConfiguration,
        metkit::codes::CodesHandle
    >;

extern template class GenericFrozenEncoder<
    eckit::LocalConfiguration,
    eckit::LocalConfiguration,
    eckit::LocalConfiguration,
    eckit::LocalConfiguration,
    metkit::codes::CodesHandle
>;

} // namespace metkit::mars2grib::backend