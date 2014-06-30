
// calculate fibonacci 

// recursive
fib := method(n,

	if(n==1,return 1)
	if(n==2,return 1)
	
  return fib(n-1) + fib(n-2)

)

// loop version

fib_loop := method(n,
	a := 0
	b := 1
	for(i,1,n-1,1,
		tmp := b
		b = a + b
		a = tmp
	)
	return b
)


for(i,1,10,1,fib_loop(i) println)
