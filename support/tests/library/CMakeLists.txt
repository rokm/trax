
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../src)

ADD_EXECUTABLE(test_region region.c ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/region.c)
TARGET_LINK_LIBRARIES(test_region)

ADD_TEST(NAME test_library_region COMMAND test_region)
