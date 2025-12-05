#pragma once

#include <map>
#include <string>
#include <array>
#include <utility>
#include "concept_core.h"

#include "impl/analysisConcept.h"
#include "impl/climatedtConcept.h"
#include "impl/compositionConcept.h"
#include "impl/datatypeConcept.h"
#include "impl/dirfreqConcept.h"
#include "impl/ensembleConcept.h"
#include "impl/extremesdtConcept.h"
#include "impl/gridtypeConcept.h"
#include "impl/levelConcept.h"
#include "impl/longrangeConcept.h"
#include "impl/marsConcept.h"
#include "impl/modelConcept.h"
#include "impl/ondemandextremesdtConcept.h"
#include "impl/originConcept.h"
#include "impl/packingConcept.h"
#include "impl/paramConcept.h"
#include "impl/periodConcept.h"
#include "impl/pointintimeConcept.h"
#include "impl/randompatternsConcept.h"
#include "impl/referencetimeConcept.h"
#include "impl/satelliteConcept.h"
#include "impl/satellitesConcept.h"
#include "impl/statisticsConcept.h"
#include "impl/tablesConcept.h"

// ======================================================
// Registry: (concept, variantName) -> table 3x5
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
struct ConceptRegistry
{
    using FnPtr =
        uint8_t(*)(const MarsDict_t&,
                   const GeoDict_t&,
                   const ParDict_t&,
                   const OptDict_t&,
                   OutDict_t&);

    using Table = std::array<std::array<FnPtr, NUM_SECTIONS>, NUM_STAGES>;

    std::map<std::pair<std::string,std::string>, Table> map;

    void add(std::string_view conceptName,
             std::string_view variantName,
             Table table)
    {
        map.emplace(
            std::make_pair(
                std::string(conceptName),
                std::string(variantName)),
            std::move(table)
        );
    }
};


// ======================================================
// make_concept_registry()
// Registers ALL concepts
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
ConceptRegistry<
    MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t
>
make_concept_registry()
{
    using Registry = ConceptRegistry<
        MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t>;

    Registry registry;

    // ============ ONE LINE PER CONCEPT ================
    RegisterVariants<AnalysisConceptInfo, AnalysisList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<ClimatedtConceptInfo, ClimatedtList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<CompositionConceptInfo, CompositionList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<DatatypeConceptInfo, DatatypeList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<DirfreqConceptInfo, DirfreqList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<EnsembleConceptInfo, EnsembleList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<ExtremesdtConceptInfo, ExtremesdtList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<GridtypeConceptInfo, GridtypeList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<LevelConceptInfo, LevelList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<LongrangeConceptInfo, LongrangeList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<MarsConceptInfo, MarsList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<ModelConceptInfo, ModelList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<OndemandextremesdtConceptInfo, OndemandextremesdtList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<OriginConceptInfo, OriginList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<PackingConceptInfo, PackingList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<ParamConceptInfo, ParamList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<PeriodConceptInfo, PeriodList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<PointintimeConceptInfo, PointintimeList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<RandompatternsConceptInfo, RandompatternsList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<ReferencetimeConceptInfo, ReferencetimeList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<SatelliteConceptInfo, SatelliteList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<SatellitesConceptInfo, SatellitesList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<StatisticsConceptInfo, StatisticsList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    RegisterVariants<TablesConceptInfo, TablesList,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);

    return registry;
}

