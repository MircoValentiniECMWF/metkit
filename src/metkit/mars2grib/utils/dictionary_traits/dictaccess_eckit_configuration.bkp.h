#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <type_traits>
#include <cstdint>

#include "eckit/config/LocalConfiguration.h"
#include "Mars2GribException.h"
#include "metkit/mars2grib/utils/generic_dict_utils.h"

namespace metkit::mars2grib::utils {

using std::operator""s;

template<> constexpr std::string_view type_name<eckit::LocalConfiguration>()  { return "eckit::LocalConfiguration"; }

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


//----------------------------------------------------------------------------------------------------------------------
// Primary template (fallback for unsupported types)
//----------------------------------------------------------------------------------------------------------------------

template<class Dict, class T>
struct DictGetOrThrow {
    static T get_or_throw(const Dict&, std::string_view) {
        throw Mars2GribException(
            "No DictGetOrThrow specialization found for this type",
            Here()
        );
    }
};

//----------------------------------------------------------------------------------------------------------------------
// BOOL
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, bool> {
    static bool get_or_throw(const eckit::LocalConfiguration& cfg,
                             std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isBoolean(k) ) {
                return cfg.getBool(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a boolean",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while reading boolean key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// INTEGER TYPES
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, int> {
    static int get_or_throw(const eckit::LocalConfiguration& cfg,
                            std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegral(k) ) {
                return cfg.getInt(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not an integral",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while reading integer key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, long> {
    static long get_or_throw(const eckit::LocalConfiguration& cfg,
                             std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegral(k) ) {
                return cfg.getLong(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not an integral",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while reading long key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::size_t> {
    static std::size_t get_or_throw(const eckit::LocalConfiguration& cfg,
                                    std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegral(k) ) {
                return cfg.getUnsigned(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not an unsigned integral",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while reading size_t key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::int32_t> {
    static std::int32_t get_or_throw(const eckit::LocalConfiguration& cfg,
                                     std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegral(k) ) {
                return cfg.getInt32(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a 32-bit integer",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading 32-bit key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::int64_t> {
    static std::int64_t get_or_throw(const eckkit::LocalConfiguration& cfg,
                                     std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegral(k) ) {
                return cfg.getInt64(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a 64-bit integer",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rerethrow_with_nested(
                Mars2GribException(
                    "Internal error reading 64-bit key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// FLOATING-POINT TYPES
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, float> {
    static float get_or_throw(const eckit::LocalConfiguration& cfg,
                              std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isFloatingPoint(k) ) {
                return cfg.getFloat(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a float",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading float key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, double> {
    static double get_or_throw(const eckit::LocalConfiguration& cfg,
                               std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isFloatingPoint(k) ) {
                return cfg.getDouble(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a double",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading double key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// STRING
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::string> {
    static std::string get_or_throw(const eckit::LocalConfiguration& cfg,
                                    std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isString(k) ) {
                return cfg.getString(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a string",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading string key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// SUBCONFIGURATION
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, eckit::LocalConfiguration> {
    static eckit::LocalConfiguration get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isSubConfiguration(k) ) {
                return cfg.getSubConfiguration(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a sub-configuration",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading sub-configuration `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// ARRAY SPECIALIZATIONS
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<int>> {
    static std::vector<int> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegralList(k) ) {
                return cfg.getIntVector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not an integral array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading integer-list key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<long>> {
    static std::vector<long> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegralList(k) ) {
                return cfg.getLongVector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not an integral array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading long-array key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<std::size_t>> {
    static std::vector<std::size_t> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegralList(k) ) {
                return cfg.getUnsignedVector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not an unsigned integral array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading unsigned-array key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<std::int32_t>> {
    static std::vector<std::int32_t> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegralList(k) ) {
                return cfg.getInt32Vector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a 32-bit integral array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading int32-array key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<std::int64_t>> {
    static std::vector<std::int64_t> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isIntegralList(k) ) {
                return cfg.getInt64Vector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a 64-bit integral array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading int64-array key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<float>> {
    static std::vector<float> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isFloatingPointList(k) ) {
                return cfg.getFloatVector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a float array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading float-array key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<double>> {
    static std::vector<double> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isFloatingPointList(k) ) {
                return cfg.getDoubleVector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a double array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading double-array key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<std::string>> {
    static std::vector<std::string> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isStringList(k) ) {
                return cfg.getStringVector(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a string array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading string-array key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictGetOrThrow<eckit::LocalConfiguration, std::vector<eckit::LocalConfiguration>> {
    static std::vector<eckit::LocalConfiguration> get_or_throw(
        const eckit::LocalConfiguration& cfg,
        std::string_view key)
    {
        const std::string k{ key };

        try {
            if ( !cfg.has(k) ) {
                throw Mars2GribException(
                    "Missing key `"s + k + "`",
                    Here()
                );
            }

            if ( cfg.isSubConfigurationList(k) ) {
                return cfg.getSubConfigurations(k);
            }
            else {
                throw Mars2GribException(
                    "Key `"s + k + "` is not a sub-configuration array",
                    Here()
                );
            }
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error reading sub-configuration array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// OPTIONAL GET (quiet version)
//----------------------------------------------------------------------------------------------------------------------

template<class T>
struct DictGet<eckit::LocalConfiguration, T> {
    static std::optional<T> get(const eckit::LocalConfiguration& cfg,
                                std::string_view key)
    {
        const std::string k{ key };

        try {
            // Reuse the safe version
            return DictGetOrThrow<eckit::LocalConfiguration, T>::get_or_throw(cfg, key);
        }
        catch (...) {
            return std::nullopt;
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------------------------
// PRIMARY TEMPLATE (fallback)
//----------------------------------------------------------------------------------------------------------------------

template<class Dict, class T>
struct DictSetOrThrow {
    static void set_or_throw(Dict&,
                             std::string_view,
                             const T&)
    {
        throw Mars2GribException(
            "No DictSetOrThrow specialization found for this type",
            Here()
        );
    }
};

template<class Dict, class T>
struct DictSetOrIgnore {
    static void set_or_ignore(Dict&,
                              std::string_view,
                              const T&)
    {
        // Silent fallback
    }
};

//----------------------------------------------------------------------------------------------------------------------
// INTERNAL HELPER FOR ERRORS
//----------------------------------------------------------------------------------------------------------------------

inline void throwTypeMismatch(const std::string& key,
                              const std::string& expected)
{
    throw Mars2GribException(
        "Unable to set key `"s + key + "` as " + expected,
        Here()
    );
}

//----------------------------------------------------------------------------------------------------------------------
// BOOL
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, bool> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const bool& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting boolean key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting boolean key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, bool> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const bool& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// INTEGRAL TYPES
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, int> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const int& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting integer key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting integer key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, int> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const int& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// long
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, long> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const long& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting long key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting long key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, long> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const long& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// size_t
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::size_t> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::size_t& value)
    {
        const std::string k{ key };

        try {
            cfg.setUnsigned(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting size_t key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting size_t key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::size_t> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::size_t& value)
    {
        try {
            cfg.setUnsigned(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// int32
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::int32_t> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::int32_t& value)
    {
        const std::string k{ key };

        try {
            cfg.setInt32(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting int32 key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting int32 key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::int32_t> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::int32_t& value)
    {
        try {
            cfg.setInt32(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// int64
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::int64_t> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::int64_t& value)
    {
        const std::string k{ key };

        try {
            cfg.setInt64(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting int64 key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting int64 key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::int64_t> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::int64_t& value)
    {
        try {
            cfg.setInt64(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// FLOATING-POINT TYPES
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, float> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const float& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting float key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting float key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, float> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const float& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, double> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const double& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting double key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting double key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, double> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const double& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// STRING
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::string> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::string& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error while setting string key `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error while setting string key `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::string> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::string& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// SUBCONFIGURATION
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, eckit::LocalConfiguration> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const eckit::LocalConfiguration& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (const std::exception&) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Internal error setting sub-configuration `"s + k + "`",
                    Here()
                )
            );
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Unknown error setting sub-configuration `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, eckit::LocalConfiguration> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const eckit::LocalConfiguration& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------
// ARRAYS
//----------------------------------------------------------------------------------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<int>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<int>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting integer-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<int>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<int>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<long>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<long>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<long>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting long-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<long>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<long>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<size_t>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<std::size_t>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<std::size_t>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting unsigned-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<std::size_t>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<std::size_t>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<int32_t>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<std::int32_t>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<std::int32_t>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting int32-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<std::int32_t>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<std::int32_t>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<int64_t>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<std::int64_t>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<std::int64_t>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting int64-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<std::int64_t>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<std::int64_t>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<float>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<float>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<float>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting float-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<float>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<float>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<double>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<double>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<double>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting double-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<double>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<double>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<string>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<std::string>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<std::string>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting string-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<std::string>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<std::string>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//-----------------------------------------------
// vector<LocalConfiguration>
//-----------------------------------------------

template<>
struct DictSetOrThrow<eckit::LocalConfiguration, std::vector<eckit::LocalConfiguration>> {
    static void set_or_throw(eckit::LocalConfiguration& cfg,
                             std::string_view key,
                             const std::vector<eckit::LocalConfiguration>& value)
    {
        const std::string k{ key };

        try {
            cfg.set(k, value);
        }
        catch (const Mars2GribException&) {
            throw;
        }
        catch (...) {
            std::rethrow_with_nested(
                Mars2GribException(
                    "Error setting subconfig-array `"s + k + "`",
                    Here()
                )
            );
        }
    }
};

template<>
struct DictSetOrIgnore<eckit::LocalConfiguration, std::vector<eckit::LocalConfiguration>> {
    static void set_or_ignore(eckit::LocalConfiguration& cfg,
                              std::string_view key,
                              const std::vector<eckit::LocalConfiguration>& value)
    {
        try {
            cfg.set(std::string(key), value);
        }
        catch (...) {
            // Ignore
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------


} // namespace metkit::mars2grib::utils
