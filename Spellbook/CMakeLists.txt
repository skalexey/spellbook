# CMakeList.txt : CMake project for Spellbook, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(Spellbook)

if(MSVC)
	# fix __cplusplus macro for MSVC
	add_compile_options(
		"/Zc:__cplusplus"
		"/std:c++latest"
	)
else()
	set(CMAKE_CXX_STANDARD 20)
endif()

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if (LOG_ON)
	add_compile_definitions("LOG_ON")
	message("Spellbook: LOG_ON is defined")
else()
	message("Spellbook: LOG_ON is not defined")
endif ()
if (LOG_LEVEL_VERBOSE)
	add_compile_definitions("LOG_LEVEL_VERBOSE")
	message("Spellbook: LOG_LEVEL_VERBOSE is defined")
else()
	message("Spellbook: LOG_LEVEL_VERBOSE is not defined")
endif ()
if (LOG_LEVEL_DEBUG)
	add_compile_definitions("LOG_LEVEL_DEBUG")
	message("Spellbook: LOG_LEVEL_DEBUG is defined")
else()
	message("Spellbook: LOG_LEVEL_DEBUG is not defined")
endif()

# Inherit parent libs logic
set(PARENT_LIBS ${PARENT_LIBS} ${LIBS})
set(PARENT_LIBS ${PARENT_LIBS} PARENT_SCOPE)
if (Spellbook_INHERIT_PARENT_LIBS)
	set(LIBS ${PARENT_LIBS})
	if (Spellbook_CMAKE_VERBOSE)
		message("Spellbook PARENT_LIBS: ${PARENT_LIBS}")
	endif()
endif()
# End of Inherit parent libs logic

# set build folder name variable for any dependency
if (CMAKE_CXX_COMPILER EQUAL "g++")
	set(BUILD_DIR_NAME "Build-g++")
else ()
	set(BUILD_DIR_NAME "Build-cmake")
endif ()

# set deps variables
set(Spellbook_DEPS "$ENV{Spellbook_deps}")
set(Spellbook_DEPS "${Spellbook_DEPS}" PARENT_SCOPE)
if ("${DEPS}" STREQUAL "")
	set(DEPS ${Spellbook_DEPS})
endif()
if ("${Spellbook_DEPS}" STREQUAL "")
	set(DEPS "$ENV{build_deps}")
endif()
if ("${DEPS}" STREQUAL "")
	message(SEND_ERROR "Spellbook: ERROR: DEPS is not specified. Take the default value")
	set(DEPS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
else()
	message("Spellbook: DEPS: ${DEPS}")
endif()
set(DEPS ${DEPS} PARENT_SCOPE)

# Utils library dependency
set(UTILS_DIR "${DEPS}/Utils")
add_subdirectory ("${UTILS_DIR}" "${UTILS_DIR}/${BUILD_DIR_NAME}")
set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES} ${utils_INCLUDES})

# DMBCore dependency
if ("${DMBCORE_DIR}" STREQUAL "")
	set(DMBCORE_DIR "${DEPS}/DataModelBuilder/Core")
else()
	message("Spellbook: DMBCORE_DIR: ${DMBCORE_DIR}")
endif()
add_subdirectory("${DMBCORE_DIR}" "${DMBCORE_DIR}/${BUILD_DIR_NAME}")
set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES} ${DMBCORE_INCLUDES})

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
message("Spellbook: Include ROOT_DIR: '${ROOT_DIR}'")

set(Spellbook_INCLUDES
	"${PROJECT_SOURCE_DIR}/include"
	"${CUSTOM_INCLUDES}"
	"${INCLUDES}"
)

set(Spellbook_INCLUDES ${Spellbook_INCLUDES} PARENT_SCOPE)
message("Spellbook: Spellbook_INCLUDES: ${Spellbook_INCLUDES}")

include_directories("${ROOT_DIR}")
include_directories("${Spellbook_INCLUDES}")
#include_directories(${PROJECT_BINARY_DIR})

# Fetch CPP from external includes
if (NOT "${INCLUDES}" STREQUAL "")
	message("Spellbook: External INCLUDES variable: ${INCLUDES}")
	foreach(items ${INCLUDES})
		file(GLOB_RECURSE INCLUDES_SRC "${items}/*.cpp")
	endforeach()
	message("Spellbook: External INCLUDES sources: ${INCLUDES_SRC}")
endif()

# set up sources
file(GLOB SRC CONFIGURE_DEPENDS "src/*.cpp" "src/spells/*.cpp" "../generated/*.cpp")
file(GLOB HEADERS ${HEADERS} "include/*.h" "include/spells/*.h" "../generated/*.h")

# Inherit parent sources logic
set(PARENT_SRC ${PARENT_SRC} ${SRC})
set(PARENT_SRC ${PARENT_SRC} PARENT_SCOPE)
if (Spellbook_INHERIT_PARENT_SRC)
	set(SRC ${PARENT_SRC})
	if (Spellbook_CMAKE_VERBOSE)
		message("Spellbook PARENT_SRC: ${PARENT_SRC}")
	endif()
endif()
# End of Inherit parent sources logic

# check sources
message("HEADERS: ${HEADERS}")
message("SRC: ${SRC}")

add_executable(Spellbook ${SRC} ${HEADERS})

target_link_libraries(Spellbook DMBCore)
target_link_libraries(Spellbook utils)

# Link all librariles including inherited
set(cnt 1)
foreach(item ${LIBS})
	if (${cnt} EQUAL 1)
		if (Spellbook_CMAKE_VERBOSE)	
			message("Link library '${item}'")
		endif()
		set(lib_name ${item})
	elseif(${cnt} EQUAL 2)
		if (Spellbook_CMAKE_VERBOSE)
			message("Library '${lib_name}' path: ${item}")
		endif()
		set(lib_path ${item})
	elseif(${cnt} EQUAL 3)
		if (Spellbook_CMAKE_VERBOSE)
			message("Library '${lib_name}' binary path: ${item}")
		endif()
		#add_subdirectory("${lib_path}" "${item}")
		target_link_libraries(Spellbook ${lib_name})
	endif()
	MATH(EXPR cnt "${cnt}+1")
endforeach()

# add_custom_command(
#     TARGET Spellbook PRE_BUILD
#     COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/../get_dependencies.sh "${CMAKE_CURRENT_SOURCE_DIR}/.." ${CMAKE_BUILD_TYPE}
#     VERBATIM
# )

add_custom_command(
    TARGET Spellbook PRE_BUILD
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/../deliver_resources.sh "${CMAKE_CURRENT_SOURCE_DIR}/.." ${CMAKE_BUILD_TYPE}
    VERBATIM
)