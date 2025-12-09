#include <iostream>

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

  // Exit point
  return 0;

};
