#include <iostream>
#include <vector>
#include <string>
#include <optional>

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

CASE("Test generic get<long>") {

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ step: 12 })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "step" using the generic get function
    long expected_result = 12;
    std::optional<long> actual_result = metkit::mars2grib::utils::get<long>(cfg, "step" );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}

CASE("Test generic get<double>") {

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ lat: 45.5 })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "lat" using the generic get function
    double expected_result = 45.5;
    std::optional<double> actual_result = metkit::mars2grib::utils::get<double>(cfg, "lat" );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}

CASE("Test generic get<bool>") {

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ flag: true })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "flag" using the generic get function
    bool expected_result = true;
    std::optional<bool> actual_result = metkit::mars2grib::utils::get<bool>(cfg, "flag" );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}

CASE("Test generic get<string>") {

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ name: test })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "name" using the generic get function
    std::string expected_result = "test";
    std::optional<std::string> actual_result = metkit::mars2grib::utils::get<std::string>(cfg, "name" );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}

CASE("Test generic get<long> with modifier"){

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ step: 12 })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "step" using the generic get function
    long expected_result = 13;
    std::optional<long> actual_result = metkit::mars2grib::utils::get<long>(cfg, "step", [](long v){ return v + 1; } );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}

CASE("Test generic get<double> with modifier"){

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ lat: 45.5 })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "lat" using the generic get function
    double expected_result = 46.7;
    std::optional<double> actual_result = metkit::mars2grib::utils::get<double>(cfg, "lat", [](double v){ return v + 1.2; } );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}

CASE("Test generic get<bool> with modifier"){

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ flag: true })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "flag" using the generic get function
    bool expected_result = false;
    std::optional<bool> actual_result = metkit::mars2grib::utils::get<bool>(cfg, "flag", [](bool v){ return !v; } );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}

CASE("Test generic get<string> with modifier"){

    // Prepare a custom dictionary to test long
    const std::string yaml(R"json({ name: test })json");

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value of "name" using the generic get function
    std::string expected_result = "test_xxx";
    std::optional<std::string> actual_result = metkit::mars2grib::utils::get<std::string>(cfg, "name", [](const std::string& v){ return v+"_xxx"; } );
    EXPECT( actual_result );
    if (  actual_result ) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }

}


CASE("Test generic get<vector<long>>") {

    // Prepare a custom dictionary
    const std::string yaml = R"yaml(
values: [1, 2, 3]
)yaml";

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value using the generic get function
    std::vector<long> expected_result = {1, 2, 3};
    std::optional<std::vector<long>> actual_result =
        metkit::mars2grib::utils::get<std::vector<long>>(
            cfg, "values"
        );

    EXPECT(actual_result);
    if (actual_result) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }
}


CASE("Test generic get<vector<double>>") {

    // Prepare a custom dictionary
    const std::string yaml = R"yaml(
values: [1.5, 2.5, 3.5]
)yaml";

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value using the generic get function
    std::vector<double> expected_result = {1.5, 2.5, 3.5};
    std::optional<std::vector<double>> actual_result =
        metkit::mars2grib::utils::get<std::vector<double>>(
            cfg, "values"
        );

    EXPECT(actual_result);
    if (actual_result) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }
}


CASE("Test generic get<vector<string>>") {

    // Prepare a custom dictionary
    const std::string yaml = R"yaml(
names: [foo, bar]
)yaml";

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value using the generic get function
    std::vector<std::string> expected_result = {"foo", "bar"};
    std::optional<std::vector<std::string>> actual_result =
        metkit::mars2grib::utils::get<std::vector<std::string>>(
            cfg, "names"
        );

    EXPECT(actual_result);
    if (actual_result) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }
}


CASE("Test generic get<vector<long>> with modifier") {

    // Prepare a custom dictionary
    const std::string yaml = R"yaml(
values: [1, 2, 3]
)yaml";

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value using the generic get function
    std::vector<long> expected_result = {2, 3, 4};
    std::optional<std::vector<long>> actual_result =
        metkit::mars2grib::utils::get<std::vector<long>>(
            cfg, "values",
            [](const std::vector<long>& v) {
                std::vector<long> out = v;
                for (auto& x : out) x += 1;
                return out;
            }
        );

    EXPECT(actual_result);
    if (actual_result) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }
}


CASE("Test generic get<vector<double>> with modifier") {

    // Prepare a custom dictionary
    const std::string yaml = R"yaml(
values: [1.5, 2.5, 3.5]
)yaml";

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value using the generic get function
    std::vector<double> expected_result = {2.5, 3.5, 4.5};
    std::optional<std::vector<double>> actual_result =
        metkit::mars2grib::utils::get<std::vector<double>>(
            cfg, "values",
            [](const std::vector<double>& v) {
                std::vector<double> out = v;
                for (auto& x : out) x += 1.0;
                return out;
            }
        );

    EXPECT(actual_result);
    if (actual_result) {
        EXPECT_EQUAL(*actual_result, expected_result);
    }
}


CASE("Test generic get<vector<string>> with modifier") {

    // Prepare a custom dictionary
    const std::string yaml = R"yaml(
names: [foo, bar]
)yaml";

    // Initialize the configuration
    const eckit::YAMLConfiguration root(yaml);
    eckit::LocalConfiguration cfg(root);

    // Try to get the value using the generic get function
    std::vector<std::string> expected_result = {"foo_x", "bar_x"};
    std::optional<std::vector<std::string>> actual_result =
        metkit::mars2grib::utils::get<std::vector<std::string>>(
            cfg, "names",
            [](const std::vector<std::string>& v) {
                std::vector<std::string> out = v;
                for (auto& x : out) x += "_x";
                return out;
            }
        );

    EXPECT(actual_result);
    if (actual_result) {
        EXPECT_EQUAL(*actual_result, expected_result);
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