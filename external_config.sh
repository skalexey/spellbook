
function job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	source $THIS_DIR/os.sh

	if [ ! -z $build_deps ]; then
		export Spellbook_deps=$build_deps
	else
		if is_windows; then
			export Spellbook_deps="${HOME}/Projects"
		else
			export Spellbook_deps="${HOME}/Projects"
		fi
		export build_deps=$Spellbook_deps
	fi
}

job $@