
function job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	source $THIS_DIR/os.sh

	if is_windows; then
		export Spellbook_deps="${HOME}/Projects"
	else
		export Spellbook_deps="${HOME}/Projects"
	fi
	[ ! -z Spellbook_deps ] && export build_deps=$Spellbook_deps
}

job $@