#!/bin/bash

deps_scenario()
{
	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} deps_scenario script]: "

	source dependencies.sh
	source deps_config.sh

	download_dependency "DataModelBuilder" "$depsLocation" "git@github.com:skalexey/DataModelBuilder.git"
	download_dependency "vl_cpp_generator" "$depsLocation" "git@github.com:skalexey/vl_cpp_generator.git"

	local enterDir=${PWD}
	cd $depsLocation/vl_cpp_generator

	log "Spellbook: Build release vl_cpp_generator" " --"

	source build.sh . release
	local retval=$?
	if [ $retval -ne 0 ]; then
		log "Error occured during vl_cpp_generator build process" " ---"
		exit 1
	else
		log "vl_cpp_generator has been successfully built" " ---"
	fi
	cd $enterDir

	# deploy cpp generator
	source deploy_cpp_generator.sh
	local retval=$?
	if [ $retval -ne 0 ]; then
		exit 1	
	fi

	local genDir="generated"

	[ ! -d "$genDir" ] && mkdir "$genDir"

	local jsonConfig=resources/spellbook.json

	log "Generate cpp code for JSON config '$jsonConfig'" " ---"

	vlcppgen $jsonConfig generated -print_root=false
	local retval=$?
	if [ $retval -ne 0 ]; then
		log "Error during cpp generation process (code: $retval)" " ---"
		exit 1
	else
		log "Cpp code generated successfully" " ---" " ------"
	fi

}

deps_scenario $@