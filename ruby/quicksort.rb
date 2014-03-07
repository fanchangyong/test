#! /usr/bin/ruby

def partition(arr,lo,hi)
	pivot=lo

	i=lo+1
	j=hi

	while true
		while true
			if i>=hi
				break
			end
			if arr[i]>=arr[pivot]
				break
			end
			i=i+1
		end

		while true
			if j<=lo 
				break
			end
			if arr[j]<=arr[pivot]
				break
			end
			j=j-1
		end

		if i>=j
			break
		end
		exch(arr,i,j)
	end

	exch(arr,j,pivot)
	return j
end

def exch(arr,i,j)
	tmp=arr[i]
	arr[i]=arr[j]
	arr[j]=tmp
end

def sort(arr,lo,hi)
	if
		lo>=hi
		return 
	end
	index=partition(arr,lo,hi)
	sort(arr,lo,index)
	sort(arr,index+1,hi)
end

def test
	#arr=10.times.map{Random.rand(1000)}
	arr=[2,1]
	puts "Before sort:"
	puts arr.to_s
	sort(arr,0,arr.size-1)
	puts "After sort:"
	puts arr.to_s
end

test
