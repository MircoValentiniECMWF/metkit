#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "eckit/config/LocalConfiguration.h"
#include "metkit/mars2grib/utils/generic_dict_utils.h"

namespace metkit::mars2grib::utils {

// ============================================================
//  eckit::LocalConfiguration è SOLO sorgente (read-only)
// ============================================================

// Presenza chiave: usa Configuration::has()
template<>
struct DictHas<eckit::LocalConfiguration> {
    static bool has(const eckit::LocalConfiguration& cfg, std::string_view key) {
        return cfg.has(std::string(key));
    }
};

// Missing: vietato per Configuration
template<>
struct DictMissing<eckit::LocalConfiguration> {

    template<class Dummy = void>
    static bool isMissing(const eckit::LocalConfiguration&, std::string_view) {
        static_assert(!std::is_same_v<Dummy, Dummy>,
            "isMissing() is NOT supported for eckit::LocalConfiguration");
        return false;
    }

    template<class Dummy = void>
    static void setMissing(eckit::LocalConfiguration&, std::string_view) {
        static_assert(!std::is_same_v<Dummy, Dummy>,
            "setMissing() is NOT supported for eckit::LocalConfiguration");
    }
};

// Lettura tipizzata: usa virtual bool get(name,T&)
template<class T>
struct DictGet<eckit::LocalConfiguration, T> {
    static std::optional<T> get(const eckit::LocalConfiguration& cfg,
                                std::string_view key) {
        T value{};
        if (cfg.get(std::string(key), value)) {
            return value;
        }
        return std::nullopt;
    }
};

// Scrittura vietata
template<class T>
struct DictSet<eckit::LocalConfiguration, T> {
    static void set(eckit::LocalConfiguration&, std::string_view, const T&) {
        static_assert(sizeof(T) == 0,
                      "eckit::LocalConfiguration is read-only in this wrapper; "
                      "writing is not allowed");
    }
};

} // namespace metkit::mars2grib::utils
