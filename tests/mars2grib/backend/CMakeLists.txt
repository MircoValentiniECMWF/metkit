add_subdirectory(sections)
add_subdirectory(concepts)


ecbuild_add_test(
  TARGET
      test-encoder

  SOURCES
      test_encoder.cc

  NO_AS_NEEDED

  LIBS
      eckit
      metkit
)