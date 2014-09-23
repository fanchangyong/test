# function

function foo(){
	echo "function foo"
	echo "22222"
	return 222;
}

result=$(foo)
echo "ret is:$?"
echo "result:$result";

exit

a=a
if [[ $a == a* ]]; then
	echo "true"
fi

exit

arr=([1]=hello [100]=world)
echo ${arr[*]}
exit



if test -a "hello"; then
	echo "hello exists"
elif test -a "world"; then
	echo "world exists"
else
	echo "neither exist"
fi

if [ -a "hello" ]; then
	echo "hello exists"
else
	echo "hello not exist"
fi

if [[ -a "hello" ]]; then
	echo "hello exist"
else
	echo "hello not exist with [["
fi

if [ 1 == 2 ]; then
	echo "1==1"
fi

if test "hello" -nt world; then
	echo "hello is newer"
else
	echo "hello is not newer"
fi

str=""
if test -z $str; then
	echo "str is empty";
else
	echo "str is $str"
	echo $str
fi

str1="hello"
str2="world"
if test str1 = str2; then
	echo "str equals str2"
else
	echo "str1 not equal str2"
fi

# case
i=b
case $i in
	[1-9]*)
		echo "i is a number"
		;;
	[a-z]*)
		echo "i is a letter"
		;;
esac

# function

