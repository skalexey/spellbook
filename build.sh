#!/bin/bash

build()
{
	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} build script]: "

	log "Build for OS: $OSTYPE" " -" " ---"

	local extraArg=" "
	local extraArgWin=$extraArg
	local extraArgMac=$extraArg

	if [ -f "deps_config.sh" ]; then
		source deps_config.sh
	fi

	source build_config.sh
	source os.sh

	if is_windows; then
		local generatorArg=" "
		local extraArg=$extraArgWin
	elif is_mac; then
		local generatorArg=" -GXcode"
		local extraArg=$extraArgMac
	else
		local generatorArg=" "
	fi

	[ ! -z "$extraArg" ] && log "Extra arguments: '$extraArg'" " -"

	# process arguments
	local buildFolderPrefix="Build"
	local onlyLibArg=" "
	local cmakeTestsArg=" "
	local cmakeGppArg=" "
	local buildConfig="Debug"
	local logArg=" -DLOG_ON=ON"
	local build=""
	local rootDirectory="."
	local onlyConfig=false


	local argIndex=0
	for arg in "$@" 
	do
		echo "arg[$argIndex]: '$arg'"
		
		if [[ $argIndex -eq 0 ]]; then
			local rootDirectory=$arg
		else
			if [[ "$arg" == "only-lib" ]]; then
				log "'only-lib' option passed. Build only library without tests" " --"
				local onlyLibArg=" only-lib"
				local cmakeTestsArg=" "
			elif [[ "$arg" == "g++" ]]; then
				log "'g++' option passed. Build with g++ compiler" " --"
				local cmakeGppArg= -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gpp
				local gppArg="g++"
				local buildFolderPrefix="Build-g++"
			elif [[ "$arg" == "no-log" ]]; then
				log "'no-log' option passed. Turn off LOG_ON compile definition" " --"
				local logArg=" "
			elif [[ "$arg" == "release" ]]; then
				log "'release' option passed. Set Release build type" " --"
				local buildConfig="Release"
			elif [[ "$arg" == "configure" ]]; then
				log "'configure' option passed. Will not build the project. Only make the config" " --"
				local onlyConfig=true
			fi
		fi	
		local argIndex=$((argIndex + 1))
	done


	# check for dependencies
	local enterDirectory=${pwd}

	if [ -f "get_dependencies.sh" ]; then
		source get_dependencies.sh $@
		local retval=$?
		if [ $retval -ne 0 ]; then
			log_error "Dependencies resolution error" " --"
			exit 1
		else
			log_success "Done with dependencies" " --"
			cd "$enterDirectory"
		fi
	fi

	[ ! -d "$rootDirectory" ] && log "Non-existent project directory passed '$rootDirectory'" " -" && exit 1 || cd "$rootDirectory"

	if [[ "$rootDirectory" != "." ]]; then
		local folderName=$rootDirectory
	fi

	log "Configure with CMake"

	local build="${buildFolderPrefix}-cmake"

	log "Output directory: '$build'" " -"

	[ ! -d "$build" ] && mkdir $build || echo "	already exists"
	cd $build

	log "cmake ..$generatorArg$logArg$extraArg" "\033[0;36m" "\033[0m"
	cmake ..$generatorArg$logArg$extraArg

	local retval=$?
	if [ $retval -ne 0 ]; then
		log_error "CMake configure error" " -"
		cd "$enterDirectory"
		exit
	else
		log_sccess "CMake configuring has been successfully done" " -"
	fi

	[ "$onlyConfig" == true ] && log "Exit without build" " -" && exit || log "Run cmake --build" " -"

	cmake --build . --config=$buildConfig

	local retval=$?
	if [ $retval -ne 0 ]; then
		log_error "CMake build error" " -"
		cd "$enterDirectory"
		exit
	else
		log_success "CMake building is successfully done" "-" " ---"
	fi

	cd "$enterDirectory"

	log_success "Finished build" " -" " ---"
}

build $@
