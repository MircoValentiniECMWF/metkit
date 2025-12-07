
ecbuild_add_test(
  TARGET
      mars2grib-dictwrappers-get-tests

  SOURCES
      mars2grib-dictwrappers-get-tests.cc

  NO_AS_NEEDED

  LIBS
      eckit
      metkit
)

ecbuild_add_test(

  TARGET
      mars2grib-dictwrappers-cond_get-tests

  SOURCES
      mars2grib-dictwrappers-cond_get-tests.cc

  NO_AS_NEEDED

  LIBS
      eckit
      metkit
)