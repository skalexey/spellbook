#!/bin/sh

buildFolderPrefix="Build"
extraArg=" -DINCLUDES=~/Projects/Utils -DDEPS=${depsLocation}"
extraArgWin=$extraArg
extraArgMac=$extraArg
buildConfig="Debug"
logArg=" -DLOG_ON=ON"
