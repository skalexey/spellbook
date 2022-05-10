#!/usr/bin/sh

source deps_config.sh

enterDir=${PWD}
cd $depsLocation/vl_cpp_generator

cp Build-cmake/Release/vl_jsontocpp /usr/local/bin/vlcppgen

retval=$?
if [ $retval -ne 0 ]; then
	echo " --- vl_cpp_generator deployment error!"
	cd $enterDir
	exit 1
else
	echo " --- vl_cpp_generator deployment success"
fi

cd $enterDir

