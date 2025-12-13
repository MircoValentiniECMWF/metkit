#pragma once

#include "metkit/mars2grib/backend/GenericFrozenEncoder.h"

#include <eckit/config/LocalConfiguration.h>
#include <metkit/codes/api/CodesAPI.h>

// dictionary traits
#include "metkit/mars2grib/utils/dictionary_traits/dictionary_access_traits.h"
#include "metkit/mars2grib/utils/dictionary_traits/dictaccess_codes_handle.h"
#include "metkit/mars2grib/utils/dictionary_traits/dictaccess_eckit_configuration.h"

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