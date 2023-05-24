package kth_largest_element_in_a_stream

import (
	"container/heap"
	"fmt"
)

type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

type KthLargest struct {
	k int
	h IntHeap
}

func Constructor(k int, nums []int) KthLargest {
	answer := KthLargest{k, IntHeap{}}
	for i := 0; i < len(nums); i++ {
		answer.Add(nums[i])
	}
	return answer
}

func (this *KthLargest) Add(val int) int {
	heap.Push(&this.h, val)
	if len(this.h) > this.k {
		heap.Pop(&this.h)
	}
	return this.h[0]
}

func Main() {
	// [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
	obj := Constructor(3, []int{4, 5, 8, 2})
	fmt.Println(obj.Add(3))
	fmt.Println(obj.Add(5))
	fmt.Println(obj.Add(10))
	fmt.Println(obj.Add(9))
	fmt.Println(obj.Add(4))
}
