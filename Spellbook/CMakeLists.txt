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

# Setup VL dependencies

if (NOT DMBCORE_DIR STREQUAL "")
	set(DMBCORE_DIR "$ENV{HOME}/${DMBCORE_DIR}")
	message("DMBCORE_DIR: ${DMBCORE_DIR}")
else()
	message("WARNING: DMBCORE_DIR is not specified")
endif()

if (NOT VL_DIR STREQUAL "")
	set(VL_DIR "$ENV{HOME}/${VL_DIR}")
	message("VL_DIR: ${VL_DIR}")
else()
	message("WARNING: VL_DIR is not specified")
endif()	

include_directories("${VL_DIR}/include")
include_directories("${VL_DIR}/JSONConverter/include")
include_directories("${DMBCORE_DIR}/include")

if (CMAKE_CXX_COMPILER EQUAL "g++")
	set(VL_BUILD_DIR_NAME "Build-g++")
	set(DMBCORE_BUILD_DIR_NAME "Build-g++")
else ()
	set(VL_BUILD_DIR_NAME "Build-cmake")
	set(DMBCORE_BUILD_DIR_NAME "Build-cmake")
endif ()

add_subdirectory("${DMBCORE_DIR}" "${DMBCORE_DIR}/${DMBCORE_BUILD_DIR_NAME}")

target_link_libraries (Spellbook DMBCore VL)

