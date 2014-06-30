
arrOfArr := list(list(1,2),list(3,4,4,5))

sum := 0
arrOfArr foreach(arr,arr foreach(v,sum = sum + v))

sum println
