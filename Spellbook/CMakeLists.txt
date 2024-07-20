
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
	# file(GLOB_RECURSE GENERATED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../generated/*.h")
	file(GLOB_RECURSE GENERATED_HEADERS "../generated/*.h")
	GROUP_SRC("${GENERATED_HEADERS}" "${CMAKE_CURRENT_SOURCE_DIR}/../generated")
	# file(GLOB_RECURSE GENERATED_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../generated/*.cpp")
	file(GLOB_RECURSE GENERATED_SOURCES "../generated/*.cpp")
	GROUP_SRC("${GENERATED_SOURCES}" "${CMAKE_CURRENT_SOURCE_DIR}/../generated")
	module_add_includes(${GENERATED_HEADERS})
	add_src(${GENERATED_SOURCES})

	# For IDE
	add_headers_to_sources()
	
	# Add executable
	module_add_executable()

	# Deliver resources.
	add_custom_command(
		TARGET Spellbook PRE_BUILD
		COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/../deliver_resources.sh "${CMAKE_CURRENT_SOURCE_DIR}/.." ${CMAKE_BUILD_TYPE}
		VERBATIM
	)
endmacro()

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()
