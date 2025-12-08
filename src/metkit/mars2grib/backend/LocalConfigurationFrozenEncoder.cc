#include "metkit/mars2grib/backend/LocalConfigurationFrozenEncoder.h"

#include <eckit/config/LocalConfiguration.h>
#include <metkit/codes/api/CodesAPI.h>

namespace metkit::mars2grib::backend {

template class GenericFrozenEncoder<
    eckit::LocalConfiguration,
    eckit::LocalConfiguration,
    eckit::LocalConfiguration,
    eckit::LocalConfiguration,
    metkit::codes::CodesHandle
>;

} // namespace metkit::mars2grib::backend