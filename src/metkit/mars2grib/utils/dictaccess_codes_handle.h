#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

#include "metkit/codes/api/CodesTypes.h"
#include "metkit/codes/api/CodesAPI.h" 
#include "metkit/mars2grib/utils/generic_dict_utils.h"

namespace metkit::mars2grib::utils {

// Alias per leggibilità
using metkit::codes::CodesHandle;
using metkit::codes::Span;

// ============================================================
//  CodesHandle è SOLO destinazione (write-only)
//  - has(dict,key) usa isDefined()
//  - isMissing/setMissing attivi
//  - get/cond_get/check/has<T> tipizzato: non disponibili
// ============================================================

// Presenza chiave: isDefined()
template<>
struct DictHas<CodesHandle> {
    static bool has(const CodesHandle& h, std::string_view key) {
        return h.isDefined(std::string(key));
    }
};

// Missing: usa isMissing / setMissing
template<>
struct DictMissing<CodesHandle> {
    static bool isMissing(const CodesHandle& h, std::string_view key) {
        return h.isMissing(std::string(key));
    }
    static void setMissing(CodesHandle& h, std::string_view key) {
        h.setMissing(std::string(key));
    }
};

// Lettura tipizzata: vietata
template<class T>
struct DictGet<CodesHandle, T> {
    static std::optional<T> get(const CodesHandle&, std::string_view) {
        static_assert(sizeof(T) == 0,
                      "Reading from metkit::codes::CodesHandle via generic "
                      "get<T>() is not allowed in this wrapper");
        return std::nullopt;
    }
};


// ============================================================
//  Scrittura tipizzata
// ============================================================

// Scalar: long
template<>
struct DictSet<CodesHandle, long> {
    static void set(CodesHandle& h, std::string_view key, const long& v) {
        h.set(std::string(key), v);
    }
};

// Scalar: int
template<>
struct DictSet<CodesHandle, int> {
    static void set(CodesHandle& h, std::string_view key, const int& v) {
        h.set(std::string(key), static_cast<long>(v));
    }
};

// Scalar: long long
template<>
struct DictSet<CodesHandle, long long> {
    static void set(CodesHandle& h, std::string_view key, const long long& v) {
        h.set(std::string(key), static_cast<long>(v));
    }
};

// Scalar: std::size_t
template<>
struct DictSet<CodesHandle, std::size_t> {
    static void set(CodesHandle& h, std::string_view key, const std::size_t& v) {
        h.set(std::string(key), static_cast<long>(v));
    }
};

// Scalar: double
template<>
struct DictSet<CodesHandle, double> {
    static void set(CodesHandle& h, std::string_view key, const double& v) {
        h.set(std::string(key), v);
    }
};

// Scalar: float
template<>
struct DictSet<CodesHandle, float> {
    static void set(CodesHandle& h, std::string_view key, const float& v) {
        h.set(std::string(key), static_cast<double>(v));
    }
};

// Scalar: std::string
template<>
struct DictSet<CodesHandle, std::string> {
    static void set(CodesHandle& h, std::string_view key, const std::string& v) {
        h.set(std::string(key), v);
    }
};


// ============================================================
//  Scrittura di vettori
// ============================================================

// vector<long>
template<>
struct DictSet<CodesHandle, std::vector<long>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<long>& v) {
        Span<const long> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

// vector<double>
template<>
struct DictSet<CodesHandle, std::vector<double>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<double>& v) {
        Span<const double> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

// vector<float>
template<>
struct DictSet<CodesHandle, std::vector<float>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<float>& v) {
        Span<const float> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

// vector<std::string>
template<>
struct DictSet<CodesHandle, std::vector<std::string>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<std::string>& v) {
        Span<const std::string> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

// vector<uint8_t> (bytes)
template<>
struct DictSet<CodesHandle, std::vector<uint8_t>> {
    static void set(CodesHandle& h, std::string_view key,
                    const std::vector<uint8_t>& v) {
        Span<const uint8_t> span(v.data(), v.size());
        h.set(std::string(key), span);
    }
};

} // namespace metkit::mars2grib::utils
