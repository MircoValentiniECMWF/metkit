#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "eckit/config/LocalConfiguration.h"
#include "metkit/mars2grib/utils/generic_dict_utils.h"

namespace metkit::mars2grib::utils {

// ============================================================
//  eckit::LocalConfiguration
// ============================================================

template<>
struct DictHas<eckit::LocalConfiguration> {
    static bool has(const eckit::LocalConfiguration& cfg, std::string_view key) {
        return cfg.has(std::string(key));
    }
};

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

template<class T>
struct DictGet<eckit::LocalConfiguration, T> {
    static std::optional<T> get(const eckit::LocalConfiguration& cfg,
                                std::string_view key) {
        const std::string k{key};

        // Scalars
        if constexpr (std::is_same_v<T, bool>) {
            if (cfg.isBoolean(k)) return cfg.getBool(k);
        }
        else if constexpr (std::is_same_v<T, int>) {
            if (cfg.isIntegral(k)) return cfg.getInt(k);
        }
        else if constexpr (std::is_same_v<T, long>) {
            if (cfg.isIntegral(k)) return cfg.getLong(k);
        }
        else if constexpr (std::is_same_v<T, std::size_t>) {
            if (cfg.isIntegral(k)) return cfg.getUnsigned(k);
        }
        else if constexpr (std::is_same_v<T, std::int32_t>) {
            if (cfg.isIntegral(k)) return cfg.getInt32(k);
        }
        else if constexpr (std::is_same_v<T, std::int64_t>) {
            if (cfg.isIntegral(k)) return cfg.getInt64(k);
        }
        else if constexpr (std::is_same_v<T, float>) {
            if (cfg.isFloatingPoint(k)) return cfg.getFloat(k);
        }
        else if constexpr (std::is_same_v<T, double>) {
            if (cfg.isFloatingPoint(k)) return cfg.getDouble(k);
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            if (cfg.isString(k)) return cfg.getString(k);
        }
        else if constexpr (std::is_same_v<T, eckit::LocalConfiguration>) {
            if (cfg.isSubConfiguration(k)) {
                return cfg.getSubConfiguration(k);
            }
        }
        // Arrays
        else if constexpr (std::is_same_v<T, std::vector<int>>) {
            if (cfg.isIntegralList(k)) return cfg.getIntVector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<long>>) {
            if (cfg.isIntegralList(k)) return cfg.getLongVector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<std::size_t>>) {
            if (cfg.isIntegralList(k)) return cfg.getUnsignedVector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<std::int32_t>>) {
            if (cfg.isIntegralList(k)) return cfg.getInt32Vector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<std::int64_t>>) {
            if (cfg.isIntegralList(k)) return cfg.getInt64Vector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<float>>) {
            if (cfg.isFloatingPointList(k)) return cfg.getFloatVector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<double>>) {
            if (cfg.isFloatingPointList(k)) return cfg.getDoubleVector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
            if (cfg.isStringList(k)) return cfg.getStringVector(k);
        }
        else if constexpr (std::is_same_v<T, std::vector<eckit::LocalConfiguration>>) {
            if (cfg.isSubConfigurationList(k)) {
                return cfg.getSubConfigurations(k);
            }
        }
        else {
            static_assert(dependent_false<T>::value == 0,
                "Unsupported type in DictGet<LocalConfiguration, T>");
        }

        return std::nullopt;
    }
};

template<class T>
struct DictSet<eckit::LocalConfiguration, T> {
    static void set(eckit::LocalConfiguration& cfg, std::string_view key, const T& value) {
        const std::string k{key};

        if constexpr (std::is_same_v<T, bool>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, int>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, long>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, long long>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, size_t>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, float>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, double>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, const char*>) {
            cfg.set(k, value);
        }
        // ------------------ VECTOR TYPES ------------------
        else if constexpr (std::is_same_v<T, std::vector<int>>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, std::vector<long>>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, std::vector<long long>>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, std::vector<size_t>>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, std::vector<float>>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, std::vector<double>>) {
            cfg.set(k, value);
        }
        else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
            cfg.set(k, value);
        }
        // ---------------- SUB-DICTIONARY -------------------
        else if constexpr (std::is_base_of_v<eckit::Configuration, T>) {
            cfg.set(k, value);
        }
        // ---------------------------------------------------
        else {
            static_assert(dependent_false<T>::value == 0,
                "Unsupported type in DictSet<eckit::LocalConfiguration, T>");
        }
    }
};

} // namespace metkit::mars2grib::utils
