
List myAvg := method(
	sum := 0
	i := 0
	self foreach(v,
		if(v type != "Number",Exception raise("non number"))	
		sum = sum + v;i = i + 1)
	sum / i
)

list(1,2,3) myAvg println
