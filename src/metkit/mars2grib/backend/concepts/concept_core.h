#pragma once

#include <array>
#include <utility>
#include <cstdint>
#include <string>
#include <iostream>

// ======================================================
// Constants
// ======================================================
static constexpr uint8_t NUM_STAGES   = 3;
static constexpr uint8_t NUM_SECTIONS = 6;

// ======================================================
// Prototypes of different capabilities
// ======================================================
template<class MarsDict_t, class GeoDict_t, class ParDict_t, class OptDict_t, class OutDict_t>
using Fn = uint8_t(*)(const MarsDict_t&, const GeoDict_t&, const ParDict_t&, const OptDict_t&, OutDict_t&);

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
// makeConceptTable() — UPDATED SIGNATURE
// ======================================================

/*
 * The next functions are basically needed to generate a table of
 * specialized (callbacks) function pointers using constexper:
 *
 * Hare is a Pseudocode Of what happens in the next three functions
 * CompileTimeLoop: foreach stage in StagesRange:
 *   CompileTimeLoop: foreach section in SectionsRange:
 *      table[stage][section] = CompileTimeResolve(Callback<stage,section>);
 */
template<
    class ConceptInfo,
    auto Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t,
    std::size_t Stage,
    std::size_t... Secs
>
constexpr std::array<Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>, sizeof...(Secs)>
makeStageRow(std::index_sequence<Secs...>) {
    return {{
        ConceptInfo::template entry<
            Stage, Secs,              // Stage, Sec
            Variant,                  // Variant
            MarsDict_t, GeoDict_t,
            ParDict_t, OptDict_t,
            OutDict_t
        >()...
    }};
}


template<
    class ConceptInfo,
    auto Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t,
    std::size_t... Stages
>
constexpr std::array<
    std::array<Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>, NUM_SECTIONS>,
    sizeof...(Stages)
>
makeTable(std::index_sequence<Stages...>) {
    return {{
        makeStageRow<
            ConceptInfo,
            Variant,
            MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t,
            Stages
        >(std::make_index_sequence<NUM_SECTIONS>{})...
    }};
}

template<
    class ConceptInfo,
    auto Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
constexpr auto makeConceptTable() {
    using Fn_t    = Fn<MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>;
    using Table_t = std::array<std::array<Fn_t, NUM_SECTIONS>, NUM_STAGES>;

    return makeTable<
        ConceptInfo,
        Variant,
        MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t
    >(std::make_index_sequence<NUM_STAGES>{});
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
