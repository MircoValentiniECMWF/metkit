#pragma once

#include <array>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

#include "metkit/mars2grib/backend/concepts/concept_core.h"
#include "metkit/mars2grib/backend/sections/sections_recipes.h"



namespace metkit::mars2grib::utils {

// Grib sections names
inline constexpr std::array<std::string_view, NUM_SECTIONS> sectionNames = {{
    "indicator-section",
    "identification-section",
    "local-use-section",
    "grid-definition-section",
    "product-definition-section",
    "data-representation-section"
}};

// Configuration of the sections
struct Section {
    uint16_t templateNumber_;
    std::map<std::string_view, std::string_view> concepts_;
};

struct EncoderCfg {
    std::array<Section, NUM_SECTIONS> sec_;
};

// Extract the template numbers in an array format
inline std::array<uint16_t, NUM_SECTIONS>
make_template_numbers(const EncoderCfg& cfg){
    std::array<uint16_t, NUM_SECTIONS> tmplNumbersArr{};
    for ( uint32_t i=0; i<NUM_SECTIONS; ++i ) {
       tmplNumbersArr[i] = cfg.sec_[i].templateNumber_;
    }
    return tmplNumbersArr;
};

// Extract and validate the concepts
inline std::array<std::vector<std::pair<std::string_view,std::string_view>>, NUM_SECTIONS>
make_section_concepts(const EncoderCfg& cfg){
    std::array<std::vector<std::pair<std::string_view,std::string_view>>, NUM_SECTIONS> conceptsArr{};
    for ( uint16_t sid=0; sid<NUM_SECTIONS; ++sid ) {
      conceptsArr[sid].clear();

      auto Concepts = metkit::mars2grib::backend::sections::resolveSectionTemplateConcepts( sid, cfg.sec_[sid].templateNumber_ );
      if ( !Concepts ){
        std::cout << "ERROR: Could not resolve concepts for section " << sid << " with template number " << cfg.sec_[sid].templateNumber_ << std::endl;
        throw std::runtime_error("Concept type mismatch");
      }

      for ( const auto& cs : *Concepts ) {
        auto it = cfg.sec_[sid].concepts_.find(cs.name);
        if (it != cfg.sec_[sid].concepts_.end()) {
            const std::string_view& conceptType = it->second;
            if ( cs.type ) {
                if ( conceptType != *cs.type ) {
                    throw std::runtime_error("Concept type mismatch");
                }
            }
            conceptsArr[sid].push_back( std::make_pair(std::string_view(cs.name), conceptType) );
        }
        else {
            conceptsArr[sid].push_back( std::make_pair(std::string_view(cs.name), std::string_view(cs.type.value_or("default")) ) );
        }
      }
    }
    return conceptsArr;
};


} // namespace metkit::mars2grib::utils