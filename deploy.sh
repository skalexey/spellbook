#!/bin/bash

source os.sh

if is_mac; then
	deploy_dir="/usr/local/bin"
else
	deploy_dir="/usr/bin"
fi

cp Build-cmake/Spellbook/Release/Spellbook "$deploy_dir/sb"
cp resources/spellbook.json "$deploy_dir/spellbook_default.json"
[ $? -ne 0 ] && echo " --- Errors during deploying at '$deploy_dir'" || echo " --- Deployed successfully at '$deploy_dir'"