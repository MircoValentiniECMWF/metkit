#include <iostream>

#include "eckit/config/YAMLConfiguration.h"
#include "eckit/config/LocalConfiguration.h"

#include "metkit/codes/api/CodesAPI.h"
#include "metkit/mars2grib/backend/LocalConfigurationFrozenEncoder.h"
#include "metkit/mars2grib/utils/encoder_cfg.h"

int main(){

  std::cout << "Testing LocalConfigurationFrozenEncoder instantiation..." << std::endl;
  metkit::mars2grib::utils::EncoderCfg cfg = {
    {{
        {0, {{"nil", "default"}} } ,
        {0, {{"origin", "default"}, {"tables", "default"}, {"forecastTime", "default"}, {"dataType", "default"}} } ,
        {1, {{"mars", "default"}, {"longrange", "default"}} } ,
        {0, {{"shapeOfTheEarth", "default"}, {"representation", "latlon"}} } ,
        {0, {{"generatingProcess", "default"}, {"forecastTime", "default"}, {"pointInTime", "default"}, {"level", "default"}, {"param", "default"}} },
        {0, {{"packing", "simple"}} }
    }}
  };

  // Print configuration
  std::cout << "=================================================================================================" << std::endl;
  int secId =0;
  for ( const auto& sec : cfg.sec_ ) {
      std::cout << "Section " << secId << "." << sec.templateNumber_ << ":" << std::endl;
      for ( const auto& concept : sec.concepts_ ) {
          std::cout << "Section " << secId << "." << sec.templateNumber_ << ": Concept " << concept.first << " / " << concept.second << std::endl;
      }
      ++secId;
  }
  std::cout << "=================================================================================================" << std::endl << std::endl << std::endl << std::endl;


  metkit::mars2grib::backend::LocalConfigurationFrozenEncoder encoder( cfg );

  encoder.debug_print();

  // Config reale da YAML
  const std::string yaml(R"json({
step: 12,
lat: 45.5,
flag: true,
name: test
})json");

  const eckit::YAMLConfiguration root(yaml);
  eckit::LocalConfiguration mars(root);
  eckit::LocalConfiguration geo(root);
  eckit::LocalConfiguration par(root);
  eckit::LocalConfiguration opt(root);

  auto handlePtr = metkit::codes::codesHandleFromSample("GRIB2");
  auto& out   = *handlePtr;

  encoder.encode( mars, geo, par, opt, out );

  // Exit point
  return 0;

};
