
echo $0

dir_name=$(dirname $0)
abs_path=`cd $dir_name;pwd;cd -`
echo "abs_path:$abs_path"
echo "now pwd:$(pwd)"
echo "dirname:$dir_name"
rl=$(readlink $dir_name)
echo "rl:$rl"


