#!/usr/bin/bash

buildFolder="Build-cmake"
fileName="spellbook.json"
databaseFile="resources/$fileName"

curDir=$PWD

echo "Current dir: $curDir"

if [ ! -z "$1" ]; then
	cd "$1"
	echo "Now in '$1'"
fi

destPath="$buildFolder/Spellbook"
destFilePath="$destPath/$fileName"
rm "$destFilePath"
echo "Copy '$databaseFile' to the build folder $destPath/"
cp "$databaseFile" "$destFilePath"

exit 0
