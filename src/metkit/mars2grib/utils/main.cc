#include <iostream>
#include <string>
#include "eckit/config/YAMLConfiguration.h"
#include "eckit/config/LocalConfiguration.h"
#include "eckit/testing/Test.h"

#include "metkit/mars2grib/utils/generic_dict_utils.h"
#include "metkit/mars2grib/utils/dictaccess_eckit_configuration.h"
#include "metkit/mars2grib/utils/dictaccess_codes_handle.h"



using metkit::mars2grib::utils::has;
using metkit::mars2grib::utils::get;
using metkit::mars2grib::utils::set;
using metkit::mars2grib::utils::cond_get;
using metkit::mars2grib::utils::forward;
using metkit::mars2grib::utils::cond_forward;
using metkit::mars2grib::utils::isMissing;
using metkit::mars2grib::utils::setMissing;

CASE("Test generic get") {
// Config reale da YAML
    const std::string yaml(R"json({
step: 12,
lat: 45.5,
flag: true,
name: test
})json");

    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);
    auto xxx = get<long>(cfg, "step" );
    EXPECT( xxx );
    if (  xxx ) {
        EXPECT_EQUAL(*xxx, 12);
    }

}

CASE("Test generic get with modifier") {
// Config reale da YAML
    const std::string yaml(R"json({
step: 12,
lat: 45.5,
flag: true,
name: test
})json");

    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);
    auto xxx = get<long>(cfg, "step", []( long v){ return v*3; } );
    EXPECT( xxx );
    if ( xxx ) {
        EXPECT_EQUAL(*xxx, 36);
    }

}


int main(int argc, char** argv) {
    return eckit::testing::run_tests(argc, argv);
}
/*
    // Config reale da YAML
    const std::string yaml(R"json({
step: 12,
lat: 45.5,
flag: true,
name: test
})json");


    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    auto handlePtr = metkit::codes::codesHandleFromSample("GRIB2");
    auto& handle   = *handlePtr;

    // Tenatative to set value
    set<long>(handle, "step", 0 );
    std::cout << "Set step to :: " << handle.getString( "step" ) << std::endl;

    // Forward
    forward<eckit::LocalConfiguration, metkit::codes::CodesHandle,long, long>(
        cfg, handle, "step", "step"
    );
    std::cout << "Forward step to :: " << handle.getString( "step" ) << std::endl;

    // Forward
    forward<eckit::LocalConfiguration, metkit::codes::CodesHandle,long, long>(
        cfg, handle, "step", "step", [](long v){ return v + 1; }
    );
    std::cout << "Forward step to :: " << handle.getString( "step" ) << std::endl;


    // Conditional Forward
    cond_forward<eckit::LocalConfiguration, metkit::codes::CodesHandle, long, long>(
        cfg, handle, "step", "step", []( long v){ return v == 27; }
    );

    if ( auto xxx = get<long>(cfg, "step", []( long v){return v * 2;} ); xxx ) {
        std::cout << "step: " <<  *xxx << std::endl;
    }

    if ( auto xxx = cond_get<long>(cfg, "step", [](long v){return (v == 2);} ); xxx ) {
        std::cout << "step: " <<  *xxx << std::endl;
    }
    else {
        std::cout << "step: not valid " << std::endl;
    }

    if ( auto xxx = get<double>(cfg, "lat"); xxx ) {
        std::cout << "lat: " <<  *xxx << std::endl;
    }

    if ( auto xxx = get<bool>(cfg, "flag"); xxx ) {
        std::cout << "flag: " <<  *xxx << std::endl;
    }

    if ( auto xxx = get<std::string>(cfg, "name"); xxx ) {
        std::cout << "name: " <<  *xxx << std::endl;
    }

  return 0;

}
*/