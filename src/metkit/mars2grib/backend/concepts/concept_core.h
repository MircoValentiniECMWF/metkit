#pragma once

#include <array>
#include <utility>
#include <cstdint>
#include <string>
#include <iostream>

// ======================================================
// ValueList
// ======================================================
template<auto... Vals>
struct ValueList { };

// ======================================================
// ForEachValue
// ======================================================
template<class List, template<auto> class Func>
struct ForEachValue;

// Non-empty list
template<auto Head, auto... Tail, template<auto> class Func>
struct ForEachValue<ValueList<Head, Tail...>, Func>
{
    template<class... Args>
    static void run(Args&&... args)
    {
        Func<Head>::apply(std::forward<Args>(args)...);
        ForEachValue<ValueList<Tail...>, Func>::run(std::forward<Args>(args)...);
    }
};

// Empty list
template<template<auto> class Func>
struct ForEachValue<ValueList<>, Func>
{
    template<class... Args>
    static void run(Args&&...) { }
};

// ======================================================
// Constants
// ======================================================
static constexpr uint8_t NUM_STAGES   = 3;
static constexpr uint8_t NUM_SECTIONS = 5;

// ======================================================
// Fn — default signature for all table functions
// ======================================================
template<class MarsDict_t, class GeoDict_t, class ParDict_t, class OptDict_t, class OutDict_t>
using Fn = uint8_t(*)(const MarsDict_t&, const GeoDict_t&, const ParDict_t&, const OptDict_t&, OutDict_t&);

// ======================================================
// makeConceptTable() — UPDATED SIGNATURE
// ======================================================
template<
    class ConceptInfo,
    auto Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
constexpr auto makeConceptTable()
{
    using Fn_t = Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>;

    std::array<std::array<Fn_t, NUM_SECTIONS>, NUM_STAGES> table{{
        { // Stage 0
            ConceptInfo::template entry<0,0,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<0,1,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<0,2,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<0,3,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<0,4,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>()
        },
        { // Stage 1
            ConceptInfo::template entry<1,0,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<1,1,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<1,2,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<1,3,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<1,4,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>()
        },
        { // Stage 2
            ConceptInfo::template entry<2,0,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<2,1,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<2,2,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<2,3,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>(),
            ConceptInfo::template entry<2,4,Variant,MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>()
        }
    }};

    return table;
}

// ======================================================
// RegisterVariantHelper — UPDATED TEMPLATE PARAM NAMES
// ======================================================
template<
    class Registry,
    class ConceptInfo,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
struct RegisterVariantHelper
{
    template<auto Variant>
    struct Func
    {
        static void apply(Registry& registry)
        {
            auto table =
                makeConceptTable<
                    ConceptInfo,
                    Variant,
                    MarsDict_t,
                    GeoDict_t,
                    ParDict_t,
                    OptDict_t,
                    OutDict_t
                >();

            registry.add(
                ConceptInfo::name,
                ConceptInfo::template variantName<Variant>(),
                std::move(table)
            );
        }
    };
};

// ======================================================
// RegisterVariants — UPDATED TEMPLATE PARAM NAMES
// ======================================================
template<
    class ConceptInfo,
    class VariantList,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
struct RegisterVariants;

template<
    class ConceptInfo,
    auto... Values,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
struct RegisterVariants<
    ConceptInfo,
    ValueList<Values...>,
    MarsDict_t,
    GeoDict_t,
    ParDict_t,
    OptDict_t,
    OutDict_t
>
{
    template<class Registry>
    static void run(Registry& registry)
    {
        using Helper =
            RegisterVariantHelper<
                Registry, ConceptInfo,
                MarsDict_t,
                GeoDict_t,
                ParDict_t,
                OptDict_t,
                OutDict_t
            >;

        ForEachValue<ValueList<Values...>, Helper::template Func>::run(registry);
    }
};
