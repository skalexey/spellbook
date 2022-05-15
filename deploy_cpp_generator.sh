#!/usr/bin/bash

deploy_cpp_generator()
{
	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} deploy_cpp_generator script]: "

	source deps_config.sh

	local enterDir=${PWD}
	local projectDir=$depsLocation/vl_cpp_generator
	cd $projectDir

	if [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
		local binDir=$projectDir/Build-cmake/Release
		local searchRes=$(echo "$PATH"|grep "$binDir")
		if [[ ! -z "$searchRes" ]]; then
			log "bin path already in the PATH variable" " --"
		else
			log "Please add vl_cpp_generator release bin directory to the system PATH variable:" " --"
			echo "$binDir" | sed -e 's/^\///' -e 's/\//\\/g' -e 's/^./\0:/'
			log "Then restart the terminal" " --"
			exit 2
		fi
		cp $binDir/vl_jsontocpp.exe $binDir/vlcppgen.exe
		local retval=$?
		if [ $retval -ne 0 ]; then
			log "vlcppgen.exe creation error" " --"
		else
			log "vlcppgen.exe created in the binary directory by path '$binDir/vlcppgen.exe'" " --"
		fi
		#cp Build-cmake/Release/vl_jsontocpp.exe /usr/bin/vlcppgen.exe
	else
		# Linux and Mac
		cp Build-cmake/Release/vl_jsontocpp /usr/local/bin/vlcppgen
	fi

	local retval=$?
	if [ $retval -ne 0 ]; then
		if [ $retval -ne 2 ]; then
			log "vl_cpp_generator deployment error!" " -"
			cd $enterDir
			exit 1
		else
			log "vl_cpp_generator deployment process needs action from User" " -"
		fi
	else
		log "vl_cpp_generator deployment success" " -"
	fi

	cd $enterDir
}

deploy_cpp_generator $@