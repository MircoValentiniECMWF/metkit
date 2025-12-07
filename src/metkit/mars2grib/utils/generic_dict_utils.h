#pragma once

#include <string_view>
#include <optional>
#include <type_traits>
#include <utility>

namespace metkit::mars2grib::utils {

// ============================================================
//  TRAITS ASTRATTI
// ============================================================

template<typename>
struct dependent_false : std::false_type {};

// Presenza chiave (non tipizzata)
template<class Dict>
struct DictHas {
    static bool has(const Dict&, std::string_view) {
        static_assert(dependent_false<Dict>::value == 0,
                      "DictHas not specialized for this Dict");
        return false;
    }
};

// Gestione missing (solo per alcuni Dict)
template<class Dict>
struct DictMissing {
    static bool isMissing(const Dict&, std::string_view) {
        static_assert(dependent_false<Dict>::value == 0,
                      "DictMissing not specialized for this Dict");
        return false;
    }
    static void setMissing(Dict&, std::string_view) {
        static_assert(dependent_false<Dict>::value == 0,
                      "DictMissing not specialized for this Dict");
    }
};

// Lettura tipizzata (ritorna std::optional<T>)
template<class Dict, class T>
struct DictGet {
    static std::optional<T> get(const Dict&, std::string_view) {
        static_assert(dependent_false<Dict>::value == 0,
                      "DictGet not specialized for this Dict and type");
        return std::nullopt;
    }
};

// Scrittura tipizzata
template<class Dict, class T>
struct DictSet {
    static void set(Dict&, std::string_view, const T&) {
        static_assert(dependent_false<Dict>::value == 0,
                      "DictSet not specialized for this Dict and type");
    }
};

// ============================================================
//  FUNZIONI DI BASE: has / isMissing / setMissing
// ============================================================

// has<Dict>(dict,key) -> presenza chiave (semantica dipende da DictHas)
template<class Dict>
inline bool has(const Dict& dict, std::string_view key) {
    return DictHas<Dict>::has(dict, key);
}

// has<T>(dict,key) -> presenza tipizzata (solo Dict leggibili)
template<class T, class Dict>
inline bool has(const Dict& dict, std::string_view key) {
    return static_cast<bool>(DictGet<Dict, T>::get(dict, key));
}

// isMissing<Dict>(dict,key)  (solo Dict che specializzano DictMissing)
template<class Dict>
inline bool isMissing(const Dict& dict, std::string_view key) {
    return DictMissing<Dict>::isMissing(dict, key);
}

// setMissing<Dict>(dict,key) (solo Dict che specializzano DictMissing)
template<class Dict>
inline void setMissing(Dict& dict, std::string_view key) {
    DictMissing<Dict>::setMissing(dict, key);
}


// ============================================================
//  GET UTILITIES
// ============================================================

// get<T>(dict,key) -> std::optional<T>
template<class T, class Dict>
inline std::optional<T> get(const Dict& dict, std::string_view key) {
    return DictGet<Dict, T>::get(dict, key);
}

// get<T>(dict,key,transform) -> std::optional<U>
template<class T, class Dict, class Fn>
inline auto get(const Dict& dict,
                std::string_view key,
                Fn&& transform) {
    using U = decltype(std::declval<Fn>()(std::declval<T>()));

    if (auto opt = get<T>(dict, key); opt) {
        return std::optional<U>{ std::forward<Fn>(transform)(*opt) };
    }
    return std::optional<U>{};
}


// ============================================================
//  SET UTILITIES
// ============================================================

// set<T>(dict,key,value)
template<class T, class Dict>
inline void set(Dict& dict, std::string_view key, const T& value) {
    DictSet<Dict, T>::set(dict, key, value);
}


// ============================================================
//  FORWARD / COND_FORWARD
// ============================================================
//
//  forward:
//    1) forward<InDict,OutDict,InT,OutT>(in,out,keyIn,keyOut)
//         InT -> static_cast<OutT>(InT)
//    2) forward<InDict,OutDict,InT,OutT>(..., modifier)
//         InT -> modifier(InT) -> OutT
//
//  cond_forward:
//    3) cond_forward<InDict,OutDict,InT,OutT>(..., cond)
//         cond: (const InT&) -> bool
//    4) cond_forward<InDict,OutDict,InT,OutT>(..., cond, modifier)
//         cond:     (const InT&) -> bool
//         modifier: (const InT&) -> OutT
//
//  Nota: forward richiede che InDict sia leggibile (DictGet specializzato)
//        e OutDict scrivibile (DictSet specializzato).
// ============================================================

// forward senza modifier
template<class InDict, class OutDict, class InT, class OutT>
inline void forward(const InDict& inDict,
                    OutDict&      outDict,
                    std::string_view keyIn,
                    std::string_view keyOut) {
    auto v = get<InT>(inDict, keyIn);
    std::cout << "Forwarding key: " << keyIn << " " << *v;
    if (auto v = get<InT>(inDict, keyIn); v) {
        std::cout << " with value: " << *v << std::endl;
        OutT outVal = static_cast<OutT>(*v);
        set<OutT>(outDict, keyOut, outVal);
    }
}

// forward con modifier: InT -> OutT
template<class InDict, class OutDict, class InT, class OutT, class Modifier>
inline void forward(const InDict& inDict,
                    OutDict&      outDict,
                    std::string_view keyIn,
                    std::string_view keyOut,
                    Modifier&& modifier) {
    if (auto v = get<InT>(inDict, keyIn); v) {
        OutT outVal = std::forward<Modifier>(modifier)(*v);
        set<OutT>(outDict, keyOut, outVal);
    }
}


// ============================================================
//  CHECK / COND_GET 
// ============================================================

// check<T>(dict,key,cond) -> bool
template<class T, class Dict, class Cond>
inline bool check(const Dict& dict,
                  std::string_view key,
                  Cond&& condition) {
    if (auto v = get<T>(dict, key); v) {
        return std::forward<Cond>(condition)(*v);
    }
    return false;
}

// cond_get<T>(dict,key,cond) -> std::optional<T>
template<class T, class Dict, class Cond>
inline std::optional<T> cond_get(const Dict& dict,
                                 std::string_view key,
                                 Cond&& condition) {
    if (auto v = get<T>(dict, key); v) {
        if (std::forward<Cond>(condition)(*v))
            return v;
    }
    return std::nullopt;
}

// cond_get<T>(dict,key,cond,modifier) -> std::optional<T>
template<class T, class Dict, class Cond, class Modifier>
inline std::optional<T> cond_get(const Dict& dict,
                                 std::string_view key,
                                 Cond&& condition,
                                 Modifier&& modifier) {
    if (auto v = get<T>(dict, key); v) {
        if (std::forward<Cond>(condition)(*v))
            return std::optional<T>{ std::forward<Modifier>(modifier)(*v) };
    }
    return std::nullopt;
}

// ============================================================
//  COND_FORWARD
// ============================================================

// 1) cond_forward(..., cond)
template<class InDict, class OutDict,
         class InT, class OutT,
         class Cond>
inline void cond_forward(const InDict& inDict,
                         OutDict&      outDict,
                         std::string_view keyIn,
                         std::string_view keyOut,
                         Cond&& cond) {
    if (auto v = get<InT>(inDict, keyIn); v) {
        if (!std::forward<Cond>(cond)(*v))
            return;

        OutT outVal = static_cast<OutT>(*v);
        set<OutT>(outDict, keyOut, outVal);
    }
}

// 2) cond_forward(..., cond, modifier)
template<class InDict, class OutDict,
         class InT, class OutT,
         class Cond, class Modifier>
inline void cond_forward(const InDict& inDict,
                         OutDict&      outDict,
                         std::string_view keyIn,
                         std::string_view keyOut,
                         Cond&&     cond,
                         Modifier&& modifier) {
    if (auto v = get<InT>(inDict, keyIn); v) {
        if (!std::forward<Cond>(cond)(*v))
            return;

        OutT outVal = std::forward<Modifier>(modifier)(*v);
        set<OutT>(outDict, keyOut, outVal);
    }
}

} // namespace metkit::mars2grib::utils
