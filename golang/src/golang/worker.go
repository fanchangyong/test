package golang

import "fmt"

type Vector []int

func (v Vector) DoSome(i,n int,c chan int){
	var sum int
	for ;i<n;i++{
		sum += v[i]
	}
	c <- sum
}

func DoAll(v *Vector){

	c := make(chan int,NCPU)
	for i:=0;i<NCPU;i++{
		go v.DoSome(i*len(*v)/NCPU,(i+1)*len(*v)/NCPU,c)
	}

	var sum = 0
	for i:=0;i<NCPU;i++{
		sum+= <-c
	}
	fmt.Println("sum is:",sum)
}


const NCPU = 8
const LEN  = 1000

func DoWithOneCPU(){

}

func Gen_vector()*Vector{
	v := make(Vector,LEN)
	for i:=0;i<LEN;i++{
		v[i]=i
	}
	return &v
}
