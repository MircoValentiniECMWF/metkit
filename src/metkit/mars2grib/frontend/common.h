/*
 * (C) Copyright 2025- ECMWF and individual contributors.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#pragma once

#include <type_traits>
#include "eckit/config/LocalConfiguration.h"
#include "metkit/mars2grib/utils/dictaccess_eckit_configuration.h"
#include "metkit/mars2grib/utils/generic_dict_utils.h"

using metkit::mars2grib::utils::get;
using metkit::mars2grib::utils::has;
using metkit::mars2grib::utils::set;

namespace metkit::mars2grib::frontend {

//================================= Matchers =================================//

struct Range {
    int first;
    int last;
    bool contains(int x) const { return x >= first && x <= last; }
};

inline Range range(int first, int last) {
    return {first, last};
}

template <typename T>
bool matchSingle(int x, const T& arg) {
    if constexpr (std::is_same_v<T, Range>) {
        return arg.contains(x);
    }
    else {
        return arg == x;
    }
}

template <typename... T>
bool matchAny(int value, T... arg) {
    return (matchSingle(value, arg) || ...);
}

//============================ Recursive Setters =============================//

template <typename T>
void setRecursive(eckit::LocalConfiguration& config, const std::string& key, T value, bool ignoreIfAlreadySet = false) {
    const auto pos = key.find('.');
    if (pos == std::string::npos) {
        if (!ignoreIfAlreadySet || !has(config, key)) {
            set(config, key, value);
        }
    }
    else {
        auto first = key.substr(0, pos);
        auto rest  = key.substr(pos + 1);

        auto subConfig = get<eckit::LocalConfiguration>(config, first).value_or(eckit::LocalConfiguration{});
        setRecursive(subConfig, rest, value);
        set(config, first, subConfig);
    }
}

inline void setRecursiveDefault(eckit::LocalConfiguration& config, const std::string& key, const std::string& value) {
    setRecursive(config, key, value, true);
}

//============================= Special Setters ==============================//

// TODO : Replace all calls to setPDT?
inline void setPDT(eckit::LocalConfiguration& sections, const std::string& key, const std::string& value) {
    setRecursive(sections, "product-definition-section.product-categories." + key, value);
}

inline void setPointInTime(eckit::LocalConfiguration& sections) {
    setPDT(sections, "timeExtent", "pointInTime");
    setRecursiveDefault(sections, "product-definition-section.point-in-time-configurator.type", "default");
}

inline void setTypeOfLevel(eckit::LocalConfiguration& sections, const std::string& type) {
    setRecursive(sections, "product-definition-section.level-configurator.type", type);
}

inline void setFixedLevel(eckit::LocalConfiguration& sections, const std::int64_t level) {
    // TODO : Make sure level-configurator.type is set?
    setRecursive(sections, "product-definition-section.level-configurator.fixed-level", level);
}

//============================================================================//

}  // namespace metkit::mars2grib::frontend