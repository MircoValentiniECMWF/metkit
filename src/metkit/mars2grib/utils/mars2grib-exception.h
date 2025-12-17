#pragma once

#include <string>
#include <optional>
#include <exception>

#include "eckit/exception/Exceptions.h"

namespace metkit::mars2grib::utils::exceptions {

// ==========================================================
// Base exception (no metadata)
// ==========================================================
class Mars2GribGenericException :
        public eckit::Exception,
        public std::nested_exception {
public:
    Mars2GribGenericException(std::string reason,
                              const eckit::CodeLocation& loc = eckit::CodeLocation())
        : eckit::Exception(reason, loc)
    {}
};


// ==========================================================
// Rules exception (no metadata)
// ==========================================================
class Mars2GribRulesException :
        public eckit::Exception,
        public std::nested_exception {
public:
    Mars2GribRulesException( std::string reason,
                             const eckit::CodeLocation& loc = eckit::CodeLocation())
        : eckit::Exception(reason, loc)
    {}
};

// ==========================================================
// Dict Layer Exception
// ==========================================================
class Mars2GribDictException :
        public Mars2GribGenericException {
public:
    Mars2GribDictException(std::string reason,
                           const eckit::CodeLocation& loc = eckit::CodeLocation())
        : Mars2GribGenericException(reason, loc)
    {}
};


// ==========================================================
// Deduction Layer Exception (empty for now)
// ==========================================================
class Mars2GribDeductionException :
        public Mars2GribGenericException {
public:
    Mars2GribDeductionException(std::string reason,
                                const eckit::CodeLocation& loc = eckit::CodeLocation())
        : Mars2GribGenericException(reason, loc)
    {}
};


// ==========================================================
// Concept Layer Exception (with metadata!)
// ==========================================================
class Mars2GribConceptException :
        public Mars2GribGenericException {
public:

    Mars2GribConceptException(std::string name,
                              std::string variant,
                              std::string stage,
                              std::string section,
                              std::string reason,
                              const eckit::CodeLocation& loc = eckit::CodeLocation())
        : Mars2GribGenericException(reason, loc),
          conceptName_(std::move(name)),
          conceptVariant_(std::move(variant)),
          stage_(std::move(stage)),
          section_(std::move(section))
    {}

    const std::optional<std::string>& conceptName() const { return conceptName_; }
    const std::optional<std::string>& conceptVariant() const { return conceptVariant_; }
    const std::optional<std::string>& stage() const { return stage_; }
    const std::optional<std::string>& section() const { return section_; }

private:
    std::optional<std::string> conceptName_;
    std::optional<std::string> conceptVariant_;
    std::optional<std::string> stage_;
    std::optional<std::string> section_;
};


// ==========================================================
// Encoder Layer Exception (no metadata for now)
// ==========================================================
class Mars2GribEncoderException :
        public Mars2GribGenericException {
public:
    Mars2GribEncoderException(std::string reason,
                              const eckit::CodeLocation& loc = eckit::CodeLocation())
        : Mars2GribGenericException(reason, loc)
    {}
};

} // namespace metkit::mars2grib::utils::exceptions