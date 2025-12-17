
/*
 * (C) Copyright 2025- ECMWF and individual contributors.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include <sstream>
#include <unordered_set>
#include <vector>
#include "eckit/config/LocalConfiguration.h"
#include "eckit/config/YAMLConfiguration.h"
#include "eckit/exception/Exceptions.h"
#include "eckit/filesystem/LocalPathName.h"
#include "eckit/filesystem/PathName.h"

#include "metkit/mars2grib/backend/encoderConfiguration.h"
#include "metkit/mars2grib/utils/mars2grib-exception.h"


int main(int argc, char** argv) {

    // using metkit::mars2grib::utils::cfg::parseEncoderCfg;
    // using metkit::mars2grib::utils::cfg::EncoderCfg;
    // using metkit::mars2grib::utils::cfg::print_encoder_cfg;
    using metkit::mars2grib::backend::config::EncoderCfg;
    using metkit::mars2grib::backend::config::makeEncoderCallbacks;
    using metkit::mars2grib::backend::config::makeEncoderConfiguration;
    using metkit::mars2grib::backend::config::printEncoderConfiguration;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <test-cases-file>" << std::endl;
        return 1;
    }

    std::string testCasesFile = argv[1];
    std::cout << "Loading test cases from file: " << testCasesFile << std::endl;
    const eckit::LocalConfiguration testCases{eckit::YAMLConfiguration{eckit::PathName(testCasesFile)}};
    const std::vector<eckit::LocalConfiguration> testCasesList = testCases.getSubConfigurations( "test-cases" );
    eckit::Log::info() << "Loaded " << testCasesList.size() << " test cases!" << std::endl;

    size_t count = 0;
    size_t failed = 0;
    for (const auto& testCase : testCasesList) {
        const auto cfg = testCase.getSubConfiguration("encoder");
        count++;
        try {
            // EncoderCfg encoderCfg = parseEncoderCfg(cfg);
            auto encoderCfg = makeEncoderConfiguration(cfg);
            printEncoderConfiguration(encoderCfg);

        }
        catch (const std::exception& e) {
            failed++;
            std::cout << "Test case " << count << " FAILED: " << e.what() << std::endl;
        }

    }

    std::cout << "Tests run: " << count << ", Failures: " << failed << std::endl;

    return 0;
}
