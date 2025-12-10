/*
 * (C) Copyright 2025- ECMWF and individual contributors.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "encoderConfig.h"
#include <string>
#include <type_traits>
#include "eckit/config/LocalConfiguration.h"
#include "eckit/exception/Exceptions.h"
#include "eckit/log/CodeLocation.h"
#include "metkit/mars2grib/frontend/pdt.h"
#include "metkit/mars2grib/utils/dictaccess_eckit_configuration.h"
#include "metkit/mars2grib/utils/generic_dict_utils.h"

using metkit::mars2grib::utils::get;
using metkit::mars2grib::utils::has;
using metkit::mars2grib::utils::set;

namespace metkit::mars2grib::frontend {

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

void setRecursiveDefault(eckit::LocalConfiguration& config, const std::string& key, const std::string& value) {
    setRecursive(config, key, value, true);
}

//============================================================================//

// TODO : Replace all calls to setPDT
void setPDT(eckit::LocalConfiguration& sections, const std::string& key, const std::string& value) {
    setRecursive(sections, "product-definition-section.product-categories." + key, value);
}

//============================================================================//

// setPointInTime
void setPointInTime(eckit::LocalConfiguration& sections) {
    setPDT(sections, "timeExtent", "pointInTime");
    setRecursiveDefault(sections, "product-definition-section.point-in-time-configurator.type", "default");
}

// setTimeRange
// setTypeOfStatisticalProcessing
// setOverallLengthOfTimeRange

// setEnsemble
// setLargeEnsemble
// setReforecast
// setderivedForecast

// setChemical

// setPeriodRange

// setDirFreq

// setSatellite

// setRandomPatterns

void setTypeOfLevel(eckit::LocalConfiguration& sections, const std::string& type) {
    setRecursive(sections, "product-definition-section.level-configurator.type", type);
}

// setFixedLevel(level)

//================================= Defaults =================================//

void setDefaults(eckit::LocalConfiguration& sections) {
    setRecursive(sections, "type", "grib2");

    // Section 0 -- Indicator
    setRecursive(sections, "indicator-section.template-number", 0);

    // Section 1 -- Identification
    setRecursive(sections, "identification-section.template-number", 0);
    setRecursive(sections, "identification-section.tables-configurator.type", "default");
    setRecursive(sections, "identification-section.tables-configurator.local-tables-version", 0);
    setRecursive(sections, "identification-section.origin-configurator.type", "default");
    setRecursive(sections, "identification-section.origin-configurator.sub-centre", 0);
    setRecursive(sections, "identification-section.data-type-configurator.type", "default");
    setRecursive(sections, "identification-section.reference-time-configurator.type", "default");

    // Section 2 -- Local use
    setRecursive(sections, "local-use-section.template-number", 0);

    // Section 3 -- Grid
    setRecursive(sections, "grid-definition-section.template-number", 0);

    // Section 4 -- Product definition
    // TODO -- Some stuff still missing?
    setRecursive(sections, "product-definition-section.param-configurator.type", "paramId");
    setRecursive(sections, "product-definition-section.model-configurator.type", "default");
    // PDT
    setRecursive(sections, "product-definition-section.product-categories.timeExtent", "None");
    setRecursive(sections, "product-definition-section.product-categories.timeFormat", "None");
    setRecursive(sections, "product-definition-section.product-categories.spatialExtent", "None");
    setRecursive(sections, "product-definition-section.product-categories.processType", "None");
    setRecursive(sections, "product-definition-section.product-categories.processSubType", "None");
    setRecursive(sections, "product-definition-section.product-categories.productCategory", "None");
    setRecursive(sections, "product-definition-section.product-categories.productSubCategory", "None");

    // Section 5 -- Data representation
    setRecursive(sections, "data-representation-section.template-number", 0);
}

//========================= Grid Definition Section ==========================//

void setGridDefinitionSection(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    if (const auto& grid = get<std::string>(mars, "grid"); grid.has_value()) {
        switch ((*grid)[0]) {
            case 'F':
            case 'O':
                setRecursive(sections, "grid-definition-section.template-number", 40);  // Gaussian grid (GG)
                break;
            case 'N':
                if ((*grid).rfind("x") == std::string::npos) {
                    setRecursive(sections, "grid-definition-section.template-number", 40);  // Gaussian grid (GG)
                }
                else {
                    setRecursive(sections, "grid-definition-section.template-number", 0);  // Lat-long grid (LL)
                }
                break;
            case 'L':
                setRecursive(sections, "grid-definition-section.template-number", 0);  // Lat-long grid (LL)
                break;
            default:
                throw eckit::Exception{"Unknown grid \"" + *grid + "\"!", Here()};
        }
    }
    else if (has(mars, "truncation")) {
        setRecursive(sections, "grid-definition-section.template-number", 50);  // Spherical-harmonics
    }
    else {
        throw eckit::Exception("Unknown grid!", Here());
    }
}

//============================ Local Use Section =============================//

void setLocalUseSection(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    if (has(mars, "anoffset")) {
        if (get<std::string>(mars, "class") == "d1") {
            setRecursive(sections, "local-use-section.template-number", 1036);
        }
        else {  // class != d1
            setRecursive(sections, "local-use-section.template-number", 36);
        }
    }
    else {  // anoffset missing
        if (get<std::string>(mars, "class") == "d1") {
            setRecursive(sections, "local-use-section.template-number", 1001);
        }
        else {  // class != d1
            if (has(mars, "method")) {
                setRecursive(sections, "local-use-section.template-number", 15);
            }
            else {  // method missing
                if (has(mars, "channel")) {
                    const auto& type = get<std::string>(mars, "type").value_or("None");
                    if (type == "em" || type == "es") {
                        setRecursive(sections, "local-use-section.template-number", 14);
                    }
                    else {
                        throw eckit::Exception("Unsupported type \"" + type + "\"!", Here());
                    }
                }
                else {  // channel missing
                    setRecursive(sections, "local-use-section.template-number", 1);
                }
            }
        }
    }
}


//=============================== Process Type ===============================//

void setProcessType(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    if (*get<std::string>(mars, "levtype") == "al") {
        // Large ensemble
        if (!has(mars, "number")) {
            throw eckit::Exception{"Expected mars keyword \"number\"", Here()};
        }
        setPDT(sections, "processSubType", "largeEnsemble");
        setRecursiveDefault(sections, "product-definition-section.ensemble-configurator.type", "default");
        if (has(mars, "hdate")) {
            setPDT(sections, "processType", "reforecast");
        }
    }
    else {
        // Ensemble
        if (has(mars, "number")) {
            if (has(mars, "hdate")) {
                setPDT(sections, "processType", "reforecast");
            }
            setPDT(sections, "processSubType", "ensemble");
            setRecursiveDefault(sections, "product-definition-section.ensemble-configurator.type", "default");
        }
        else {
            if (has(mars, "hdate")) {
                throw eckit::Exception{"unexpected mars keyword \"hdate\"", Here()};
            }
            if (const auto& type = get<std::string>(mars, "type"); type && (*type == "em" || *type == "es")) {
                // Derived ensemble forecast
                setPDT(sections, "processType", "derivedForecast");
                setPDT(sections, "processSubType", "ensemble");
                setRecursive(sections, "product-definition-section.ensemble-configurator.type", "derived");
            }
            // Else, just pass through...
        }
    }
}

//================================ Horizontal ================================//

struct Range {
    int first;
    int last;
    bool contains(int x) const { return x >= first && x <= last; }
};

Range range(int first, int last) {
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

void setSFC(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    throw eckit::NotImplemented{Here()};
}

void setSOL(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    const auto param = *get<std::int64_t>(mars, "param");
    if (matchAny(param, 33, 74, 238, 228038, 228141, 235078, 235080, 237080, 238080, 239080)) {
        setRecursive(sections, "product-definition-section.level-configurator.type", "snowLayer");
    }
    else if (matchAny(param, 183, 235077, 260199, 260360)) {
        setRecursive(sections, "product-definition-section.level-configurator.type", "soilLayer");
    }
    else if (matchAny(param, 262000, 262024)) {
        setRecursive(sections, "product-definition-section.level-configurator.type", "seaIceLayer");
    }
    else {
        throw eckit::Exception{"Unmatched param \"" + std::to_string(param) + "\" for levtype SOL", Here()};
    }
}

void setStatistics(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    // TODO : Use automated mapping from param to typeOfStatisticalProcessing

    // Assume the param is a point-in-time field for now
    setPointInTime(sections);
}

void setHorizontal(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    if (has(mars, "channel")) {
        return;  // Bypass for satellite fields, they are handled in `setSatellite`
    }

    // TODO : Be more strict and list all the params that exists on each given levtype!
    const auto levtype = *get<std::string>(mars, "levtype");
    if (levtype == "sfc") {
        setSFC(mars, sections);
    }
    else if (levtype == "hl") {
        setRecursive(sections, "product-definition-section.level-configurator.type", "heightAboveGround");
    }
    else if (levtype == "ml") {
        setRecursive(sections, "product-definition-section.level-configurator.type", "hybrid");
    }
    else if (levtype == "pl") {
        if (get<std::int64_t>(mars, "level") >= 100) {
            setRecursive(sections, "product-definition-section.level-configurator.type", "isobaricInhPa");
        }
        else {
            setRecursive(sections, "product-definition-section.level-configurator.type", "isobaricInPa");
        }
    }
    else if (levtype == "pt") {
        setRecursive(sections, "product-definition-section.level-configurator.type", "theta");
    }
    else if (levtype == "pv") {
        setRecursive(sections, "product-definition-section.level-configurator.type", "potentialVorticity");
    }
    else if (levtype == "sol") {
        setSOL(mars, sections);
    }
    else if (levtype == "al") {
        setRecursive(sections, "product-definition-section.level-configurator.type", "abstractSingleLevel");
    }
    else {
        throw eckit::Exception{"Unknown levtype \"" + levtype + "\"", Here()};
    }

    setStatistics(mars, sections);
}

//================================ Satellite =================================//

void setSatellite(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    if (!has(mars, "channel")) {
        return;  // Not a satellite field
    }

    if (const auto& type = get<std::string>(mars, "type"); type && (*type == "em" || *type == "es")) {
        // Derived ensemble forecaste satellite
        if (*get<std::int64_t>(mars, "param") != 194) {
            throw eckit::Exception{"Param not in range!", Here()};
        }
        setPointInTime(sections);
        setTypeOfLevel(sections, "surface");
    }
    else {
        // Single satellite
        if (const auto param = *get<std::int64_t>(mars, "param"); !(param >= 260510 && param <= 260512)) {
            throw eckit::Exception{"Param not in range!", Here()};
        }
        setPointInTime(sections);
        setRecursiveDefault(sections, "product-definition-section.satellite-configurator.type", "default");
        setPDT(sections, "productCategory", "satellite");
    }
}

//======================= Data Representation Section ========================//

void setDataRepresentationSection(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    const auto& packing = get<std::string>(mars, "packing");
    if (!packing) {
        throw eckit::Exception{"Mars keyword \"packing\" is missing!", Here()};
    }
    if (*packing == "simple") {
        setRecursive(sections, "data-representation-section.template-number", 0);
    }
    else if (*packing == "ccsds") {
        setRecursive(sections, "data-representation-section.template-number", 42);
    }
    else if (*packing == "complex") {
        setRecursive(sections, "data-representation-section.template-number", 51);
    }
    else {
        throw eckit::Exception{"Unknown value \"" + *packing + "\" for mars keyword \"packing\"!", Here()};
    }
}

void setAll(const eckit::LocalConfiguration& mars, eckit::LocalConfiguration& sections) {
    setDefaults(sections);

    setGridDefinitionSection(mars, sections);
    setLocalUseSection(mars, sections);

    setProcessType(mars, sections);
    setHorizontal(mars, sections);

    setSatellite(mars, sections);
    setDataRepresentationSection(mars, sections);

    setRecursive(sections, "product-definition-section.template-number",
                 templateNumberFromPDT(
                     *get<eckit::LocalConfiguration>(sections, "product-definition-section.product-categories")));
}

eckit::LocalConfiguration buildEncoderConfig(const eckit::LocalConfiguration& mars) {
    eckit::LocalConfiguration sections;
    setAll(mars, sections);
    return sections;
}

}  // namespace metkit::mars2grib::frontend
