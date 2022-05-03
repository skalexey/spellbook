#!/usr/bin/sh

buildFolder="Build-cmake"
databaseFile="spellbook.json"

curDir=$PWD

echo "Current dir: $curDir"

if [ ! -z "$2" ]; then
	cd $2
fi

destPath="${buildFolder}/Spellbook"
destFilePath="${destPath}/${databaseFile}"
rm "${destFilePath}"
echo "Copy '$databaseFile' to the build folder $destPath/"
cp "$databaseFile" "$destFilePath"

