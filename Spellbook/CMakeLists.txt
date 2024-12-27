
cmake_minimum_required(VERSION 3.15)

project(Spellbook)

macro(setup_module)
	module_message("Setting up module: ${MODULE_NAME}")
	option(TESTS "Add Test target" OFF)
	option(CLIENT "Add vl_jsontocpp executable target" ON)

	# DMBCore dependency
	add_dependency_module(${DEPS}/DataModelBuilder/Core DMBCore)

	# Utils dependency
	set(UTILS_DIR "${DEPS}/Utils")
	module_message("UTILS_DIR: ${UTILS_DIR}")
	module_add_includes(${UTILS_DIR}/include)
	# For IDE
	file(GLOB_RECURSE UTILS_HEADERS "${UTILS_DIR}/include/*")
	GROUP_SRC("${UTILS_HEADERS}" "${UTILS_DIR}/include")

	# Add generated code
	set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../generated")
	# file(GLOB_RECURSE GENERATED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../generated/*.h")
	file(GLOB_RECURSE GENERATED_HEADERS "${GENERATED_DIR}/*.h")
	GROUP_SRC("${GENERATED_HEADERS}" "${GENERATED_DIR}")
	# file(GLOB_RECURSE GENERATED_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../generated/*.cpp")
	file(GLOB_RECURSE GENERATED_SOURCES "${GENERATED_DIR}/*.cpp")
	GROUP_SRC("${GENERATED_SOURCES}" "${GENERATED_DIR}")
	module_add_includes("${CMAKE_CURRENT_SOURCE_DIR}/..") # For includes like #include "generated/..."
	add_src(
		${UTILS_DIR}/src/file_utils.cpp
		${UTILS_DIR}/src/io_utils.cpp
		${GENERATED_SOURCES}
		${GENERATED_HEADERS}
	)

	# For IDE
	add_headers_to_sources()
	
	# Add executable
	module_add_executable()

	set_target_properties(${MODULE_NAME} PROPERTIES OUTPUT_NAME sb)

	# Deliver resources.
	add_custom_command(
		TARGET Spellbook PRE_BUILD
		COMMAND bash -c "echo 'PWD: $(pwd)' && ls && ../../deliver_resources.sh ../../ ${CMAKE_BUILD_TYPE}"
		VERBATIM
	)
endmacro()

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()
