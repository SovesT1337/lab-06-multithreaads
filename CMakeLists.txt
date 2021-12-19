cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

set(
HUNTER_CACHE_SERVERS
"https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

# TODO: rename project and delete this comment
project(template VERSION 0.1.0)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")
string(APPEND CMAKE_CXX_FLAGS " -Wno-uninitialized") ###########################################

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(${PROJECT_NAME} STATIC
# enum your files and delete this comment
${CMAKE_CURRENT_SOURCE_DIR}/sources/functions.cpp
include/picosha2.h)

add_executable(demo
${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
"$<INSTALL_INTERFACE:include>"
)
hunter_add_package(nlohmann_json)
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(demo ${PROJECT_NAME})

hunter_add_package(Boost COMPONENTS log thread system filesystem date_time)

find_package(Boost COMPONENTS REQUIRED log thread system log_setup filesystem date_time)
FIND_PACKAGE(Threads)

set(_Boost_LOG_SETUP_DEPENDENCIES log)#################################
#add_definitions(-DBOOST_LOG_DYN_LINK)#################################
SET(Boost_USE_45STATIC_LIBS ON)######################################

if(NOT Boost_FOUND)
message(FATAL_ERROR "Could not find boost!")
endif()
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(demo ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} nlohmann_json::nlohmann_json )

if(BUILD_TESTS)
add_executable(tests
# TODO: enum your files and delete this comment
${CMAKE_CURRENT_SOURCE_DIR}/tests/example.cpp
)
target_link_libraries(tests ${PROJECT_NAME} GTest::gtest_main)
enable_testing()
add_test(NAME unit_tests COMMAND tests)
endif()

if(BUILD_COVERAGE)
set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/coverage/cmake")
find_package(codecov)
string(APPEND CMAKE_CXX_FLAGS " —coverage")
add_coverage(${PROJECT_NAME})
add_coverage(tests)
coverage_evaluate()
endif()

if(BUILD_DOCS)
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/_docs)
set(DOXYGEN_EXAMPLE_PATH examples)
set(DOXYGEN_GENERATE_HTML NO)
set(DOXYGEN_GENERATE_MAN YES)
find_package(Doxygen)
doxygen_add_docs(docs include)
install(DIRECTORY ${DOXYGEN_OUTPUT_DIRECTORY}/man DESTINATION share)
# add_dependencies(install docs) need to call target docs before install or package
endif()

include(CPackConfig.cmake)

install(TARGETS ${PROJECT_NAME} demo
EXPORT "${PROJECT_NAME}-targets"
RUNTIME DESTINATION bin
ARCHIVE DESTINATION lib
LIBRARY DESTINATION lib
INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

install(EXPORT "${PROJECT_NAME}-targets"
NAMESPACE "${PROJECT_NAME}::"
DESTINATION "lib/cmake"
)