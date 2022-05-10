#!/bin/sh

source dependencies.sh
source deps_config.sh

download_dependency "DataModelBuilder" "$depsLocation" "git@github.com:skalexey/DataModelBuilder.git"
download_dependency "vl_cpp_generator" "$depsLocation" "git@github.com:skalexey/vl_cpp_generator.git"
download_dependency "Utils" "$depsLocation" "git@github.com:skalexey/Utils.git"

enterDir=${PWD}
cd $depsLocation/vl_cpp_generator
./build.sh . release
retval=$?
if [ $retval -ne 0 ]; then
	echo " --- Error occured during vl_cpp_generator build process"
	exit 1
else
	echo " --- vl_cpp_generator has been successfully built"
fi
cd $enterDir

# deploy cpp generator
source deploy_cpp_generator.sh
retval=$?
if [ $retval -ne 0 ]; then
	# Everything is OK, the deploy script returns "already deployed" error code
	exit 0
else
	echo " --- Restart the terminal and build.sh script to finish the process"
fi

genDir="generated"

[ ! -d "$genDir" ] && mkdir "$genDir"

jsonConfig=resources/spellbook.json

echo " --- Generate cpp code for JSON config '$jsonConfig'"

vlcppgen $jsonConfig generated -print_root=false
retval=$?
if [ $retval -ne 0 ]; then
	echo " --- Error during cpp generation process (code: $retval)"
	exit 1
else
	echo " --- Cpp code generated successfully"
fi


