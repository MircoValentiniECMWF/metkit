/*
 * (C) Copyright 2025- ECMWF and individual contributors.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "Grib2Encoder.h"
#include <limits>
#include "eckit/config/LocalConfiguration.h"
#include "eckit/exception/Exceptions.h"
#include "metkit/codes/api/CodesAPI.h"
// #include "metkit/mars2grib/backend/LocalConfigurationFrozenEncoder.h"
#include "metkit/mars2grib/frontend/encoderConfig.h"

#include "metkit/mars2grib/utils/dictionary_traits/dictaccess_eckit_configuration.h"
#include "metkit/mars2grib/utils/dictionary_traits/dictionary_access_traits.h"

using metkit::mars2grib::utils::dict_traits::get_opt;

namespace metkit::mars2grib {

Grib2Encoder::Grib2Encoder() : opts_{} {}
Grib2Encoder::Grib2Encoder(const eckit::LocalConfiguration& opts) : opts_{opts} {}

std::unique_ptr<metkit::codes::CodesHandle> Grib2Encoder::encode(const eckit::LocalConfiguration& mars,
                                                                 const eckit::LocalConfiguration& misc,
                                                                 const eckit::LocalConfiguration& geom,
                                                                 const std::vector<double>& values) {
    const auto conf = frontend::buildEncoderConfig(mars);

    auto sample = metkit::codes::codesHandleFromSample( "GRIB2" );
#if 0
    auto sample = backend::LocalConfigurationFrozenEncoder{conf}.encode(mars, geom, misc, opts_);

    auto bitmapPresent = get_opt<bool>(misc, "bitmapPresent").value_or(false);
    auto missingValue  = get_opt<double>(misc, "missingValue").value_or(std::numeric_limits<double>::max());

    sample->set("bitmapPresent", bitmapPresent);
    if (bitmapPresent) {
        sample->set("missingValue", missingValue);
    }

    if (get_opt<std::int64_t>(misc, "values-scale-factor").value_or(1.0) != 1.0) {
        throw eckit::NotImplemented{"Handling scale factor is not implemented!", Here()};
    }

    sample->set("values", values);
#endif

    return sample;
}

std::unique_ptr<metkit::codes::CodesHandle> Grib2Encoder::encode(const eckit::LocalConfiguration& mars,
                                                                 const eckit::LocalConfiguration& misc,
                                                                 const eckit::LocalConfiguration& geom,
                                                                 const std::vector<float>& values) {
    // ecCodes does not support setting float values (yet), we have to set them as doubles for now!
    return encode(mars, misc, geom, std::vector<double>{values.begin(), values.end()});
}

std::unique_ptr<metkit::codes::CodesHandle> Grib2Encoder::encode(const eckit::LocalConfiguration& mars,
                                                                 const eckit::LocalConfiguration& misc,
                                                                 const eckit::LocalConfiguration& geom,
                                                                 const double* values, size_t length) {
    return encode(mars, misc, geom, std::vector<double>{values, values + length});
}

std::unique_ptr<metkit::codes::CodesHandle> Grib2Encoder::encode(const eckit::LocalConfiguration& mars,
                                                                 const eckit::LocalConfiguration& misc,
                                                                 const eckit::LocalConfiguration& geom,
                                                                 const float* values, size_t length) {
    return encode(mars, misc, geom, std::vector<float>{values, values + length});
}

}  // namespace metkit::mars2grib
