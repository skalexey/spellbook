#!/usr/bin/bash

buildFolder="Build-cmake"
fileName="spellbook.json"
fileNameDefault="spellbook_default.json"
databaseFile="resources/$fileName"

curDir=$PWD

echo "Current dir: $curDir"

if [ ! -z "$1" ]; then
	cd "$1"
	echo "Now in '$1'"
fi

initial=false
if [ "$2" == "-i" ]; then
	initial=true
fi
destPath="$buildFolder/Spellbook"
destFilePath="$destPath/$fileName"
[ -f "$destFilePath" ] && rm "$destFilePath"

if ! $initial; then
	echo "Copy '$databaseFile' to the build folder $destPath/"
	cp "$databaseFile" "$destFilePath"
fi
destFilePathDefault="$destPath/$fileNameDefault"
echo "Create default config in '$destFilePathDefault'"
cp "$databaseFile" "$destFilePathDefault"

exit 0
