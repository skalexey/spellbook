# CMakeList.txt : CMake project for Spellbook, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(Spellbook)

set(CMAKE_CXX_STANDARD 20)

if (LOG_ON)
	add_compile_definitions("LOG_ON")
endif ()

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
include_directories("${ROOT_DIR}")

if (NOT INCLUDES STREQUAL "")
	include_directories("${INCLUDES}")
	message("Add extra includes: ${INCLUDES}")
endif()

file(GLOB SRC CONFIGURE_DEPENDS "src/*.cpp" "src/spells/*.cpp")
file(GLOB HEADERS ${HEADERS} "include/*.h" "include/spells/*.h")

message("HEADERS: ${HEADERS}")
message("SRC: ${SRC}")

include_directories("include")

add_executable (Spellbook ${SRC} ${HEADERS})

# Setup dependencies

if ("${DEPS}" STREQUAL "")
	message("WARNING: DEPS is not specified. Take the default value")
	set(DEPS "${PROJECT_SOURCE_DIR}/..")
else()
	message("DEPS: ${DEPS}")
endif()

if ("${DMBCORE_DIR}" STREQUAL "")
	set(DMBCORE_DIR "${DEPS}/DataModelBuilder/Core")
else()
	message("DMBCORE_DIR: ${DMBCORE_DIR}")
endif()

if (CMAKE_CXX_COMPILER EQUAL "g++")
	set(BUILD_DIR_NAME "Build-g++")
else ()
	set(BUILD_DIR_NAME "Build-cmake")
endif ()

add_subdirectory("${DMBCORE_DIR}" "${DMBCORE_DIR}/${BUILD_DIR_NAME}")

include_directories("${DMBCORE_INCLUDES}")

target_link_libraries (Spellbook DMBCore VL)

