#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

#include "metkit/codes/api/CodesTypes.h"
#include "metkit/codes/api/CodesAPI.h"
#include "metkit/mars2grib/utils/generic_dict_utils.h"

namespace metkit::mars2grib::utils {

using metkit::codes::NativeType;
using metkit::codes::CodesHandle;
using metkit::codes::Span;

template<class T>
struct NativeTypeMap;

template<> struct NativeTypeMap<long>                { static constexpr NativeType value = NativeType::Long;   };
template<> struct NativeTypeMap<int>                 { static constexpr NativeType value = NativeType::Long;   };
template<> struct NativeTypeMap<long long>           { static constexpr NativeType value = NativeType::Long;   };
template<> struct NativeTypeMap<std::size_t>         { static constexpr NativeType value = NativeType::Long;   };

template<> struct NativeTypeMap<double>              { static constexpr NativeType value = NativeType::Double; };
template<> struct NativeTypeMap<float>               { static constexpr NativeType value = NativeType::Double; };

template<> struct NativeTypeMap<std::string>         { static constexpr NativeType value = NativeType::String; };

template<> struct NativeTypeMap<std::vector<long>>   { static constexpr NativeType value = NativeType::Long;   };
template<> struct NativeTypeMap<std::vector<double>> { static constexpr NativeType value = NativeType::Double; };
template<> struct NativeTypeMap<std::vector<float>>  { static constexpr NativeType value = NativeType::Double; };

template<> struct NativeTypeMap<std::vector<std::string>> { static constexpr NativeType value = NativeType::String; };
template<> struct NativeTypeMap<std::vector<uint8_t>>     { static constexpr NativeType value = NativeType::Bytes;  };



inline bool nativeTypeMatches(CodesHandle& h,
                              std::string_view key,
                              NativeType expected)
{
    return h.isDefined(std::string(key)) &&
           h.type(std::string(key)) == expected;
}


template<>
struct DictHas<CodesHandle> {
    static bool has(const CodesHandle& h, std::string_view key) {
        return h.isDefined(std::string(key));
    }
};

template<>
struct DictMissing<CodesHandle> {
    static bool isMissing(const CodesHandle& h, std::string_view key) {
        return h.isMissing(std::string(key));
    }
    static void setMissing(CodesHandle& h, std::string_view key) {
        h.setMissing(std::string(key));
    }
};
template<class T>
struct DictGet<CodesHandle, T> {
    static std::optional<T> get(const CodesHandle&, std::string_view) {
        static_assert(sizeof(T) == 0,
                      "Reading from metkit::codes::CodesHandle via generic "
                      "get<T>() is not allowed in this wrapper");
        return std::nullopt;
    }
};


template<>
struct DictSet<CodesHandle, int> {
    static void set(CodesHandle& h, std::string_view key, const int& v) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return;
        h.set(std::string(key), static_cast<long>(v));
    }
};

template<>
struct DictSet<CodesHandle, long long> {
    static void set(CodesHandle& h, std::string_view key, const long long& v) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return;
        h.set(std::string(key), static_cast<long>(v));
    }
};

template<>
struct DictSet<CodesHandle, std::size_t> {
    static void set(CodesHandle& h, std::string_view key, const std::size_t& v) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return;
        h.set(std::string(key), static_cast<long>(v));
    }
};

template<>
struct DictSet<CodesHandle, double> {
    static void set(CodesHandle& h, std::string_view key, const double& v) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return;
        h.set(std::string(key), v);
    }
};

template<>
struct DictSet<CodesHandle, float> {
    static void set(CodesHandle& h, std::string_view key, const float& v) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return;
        h.set(std::string(key), static_cast<double>(v));
    }
};

template<>
struct DictSet<CodesHandle, std::string> {
    static void set(CodesHandle& h, std::string_view key, const std::string& v) {
        if (!nativeTypeMatches(h, key, NativeType::String)) return;
        h.set(std::string(key), v);
    }
};

template<>
struct DictSet<CodesHandle, std::vector<long>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<long>& v) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return;
        Span<const long> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

template<>
struct DictSet<CodesHandle, std::vector<double>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<double>& v) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return;
        Span<const double> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

template<>
struct DictSet<CodesHandle, std::vector<float>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<float>& v) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return;
        Span<const float> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

template<>
struct DictSet<CodesHandle, std::vector<std::string>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<std::string>& v) {
        if (!nativeTypeMatches(h, key, NativeType::String)) return;
        Span<const std::string> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

template<>
struct DictSet<CodesHandle, std::vector<uint8_t>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<uint8_t>& v) {
        if (!nativeTypeMatches(h, key, NativeType::Bytes)) return;
        Span<const uint8_t> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

template<>
struct DictGet<CodesHandle, long> {
    static std::optional<long> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return std::nullopt;

        long v{};
        if (!h.get(std::string(key), v)) return std::nullopt;
        return v;
    }
};

template<>
struct DictGet<CodesHandle, int> {
    static std::optional<int> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return std::nullopt;

        long v{};
        if (!h.get(std::string(key), v)) return std::nullopt;
        return static_cast<int>(v);
    }
};

template<>
struct DictGet<CodesHandle, long long> {
    static std::optional<long long> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return std::nullopt;

        long v{};
        if (!h.get(std::string(key), v)) return std::nullopt;
        return static_cast<long long>(v);
    }
};

template<>
struct DictGet<CodesHandle, std::size_t> {
    static std::optional<std::size_t> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return std::nullopt;

        long v{};
        if (!h.get(std::string(key), v)) return std::nullopt;
        return static_cast<std::size_t>(v);
    }
};

template<>
struct DictGet<CodesHandle, double> {
    static std::optional<double> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return std::nullopt;

        double v{};
        if (!h.get(std::string(key), v)) return std::nullopt;
        return v;
    }
};

template<>
struct DictGet<CodesHandle, float> {
    static std::optional<float> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return std::nullopt;

        double v{};
        if (!h.get(std::string(key), v)) return std::nullopt;
        return static_cast<float>(v);
    }
};

template<>
struct DictGet<CodesHandle, std::string> {
    static std::optional<std::string> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::String)) return std::nullopt;

        std::string v;
        if (!h.get(std::string(key), v)) return std::nullopt;
        return v;
    }
};

struct DictGet<CodesHandle, std::vector<long>> {
    static std::optional<std::vector<long>> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return std::nullopt;

        std::vector<long> v;
        if (!h.get(std::string(key), v)) return std::nullopt;
        return v;
    }
};

struct DictGet<CodesHandle, std::vector<int>> {
    static std::optional<std::vector<int>> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Long)) return std::nullopt;

        std::vector<long> tmp;
        if (!h.get(std::string(key), tmp)) return std::nullopt;

        std::vector<int> out(tmp.size());
        for (size_t i = 0; i < tmp.size(); ++i)
            out[i] = static_cast<int>(tmp[i]);

        return out;
    }
};

emplate<>
struct DictGet<CodesHandle, std::vector<double>> {
    static std::optional<std::vector<double>> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return std::nullopt;

        std::vector<double> v;
        if (!h.get(std::string(key), v)) return std::nullopt;
        return v;
    }
};

struct DictGet<CodesHandle, std::vector<float>> {
    static std::optional<std::vector<float>> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Double)) return std::nullopt;

        std::vector<double> tmp;
        if (!h.get(std::string(key), tmp)) return std::nullopt;

        std::vector<float> out(tmp.size());
        for (size_t i = 0; i < tmp.size(); ++i)
            out[i] = static_cast<float>(tmp[i]);

        return out;
    }
};

template<>
struct DictGet<CodesHandle, std::vector<std::string>> {
    static std::optional<std::vector<std::string>> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::String)) return std::nullopt;

        std::vector<std::string> v;
        if (!h.get(std::string(key), v)) return std::nullopt;
        return v;
    }
};

struct DictGet<CodesHandle, std::vector<uint8_t>> {
    static std::optional<std::vector<uint8_t>> get(CodesHandle& h, std::string_view key) {
        if (!nativeTypeMatches(h, key, NativeType::Bytes)) return std::nullopt;

        std::vector<uint8_t> v;
        if (!h.get(std::string(key), v)) return std::nullopt;
        return v;
    }
};


} // namespace metkit::mars2grib::utils
