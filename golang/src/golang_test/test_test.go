package golang_test

import "golang"
import "testing"

func Benchmark_Doall(b *testing.B){
	v := golang.Gen_vector()
	golang.DoAll(v)
}
