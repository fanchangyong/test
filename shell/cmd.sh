bash_source_0=${BASH_SOURCE[0]}

echo "bash source 0 is:$bash_source_0"

dir=$(dirname $bash_source_0)

echo "dir:$dir"

SCRIPT_DIR=$(readlink $dir)


echo "SCRIPT_DIR:$SCRIPT_DIR"


