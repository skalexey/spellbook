#!/bin/bash

function job()
{
	source os.sh
	
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

	if is_mac; then
		temp_dir="/var/folders/x3/s5vc1vgs4132nd81mblxzhc40000gn/T"
	else
		temp_dir="${HOME}/AppData/Local/Temp"
	fi

	cp "$temp_dir/spellbook.json" "$THIS_DIR/resources"
}

job $@