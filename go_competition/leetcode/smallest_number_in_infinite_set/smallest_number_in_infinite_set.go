package smallest_number_in_infinite_set

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

type SmallestInfiniteSet struct {
	n int
	h IntHeap
	s map[int]struct{}
}

func Constructor() SmallestInfiniteSet {
	return SmallestInfiniteSet{1, IntHeap{}, map[int]struct{}{}}
}

func (this *SmallestInfiniteSet) PopSmallest() int {
	if this.h.Len() > 0 {
		r := heap.Pop(&this.h).(int)
		delete(this.s, r)
		return r
	} else {
		this.n = this.n + 1
		return this.n - 1
	}
}

func (this *SmallestInfiniteSet) AddBack(num int) {
	if num < this.n {
		_, ok := this.s[num]
		if !ok {
			heap.Push(&this.h, num)
			this.s[num] = struct{}{}
		}
	}
}

func Main() {
	obj := Constructor()
	obj.AddBack(2)                 // 2 is already in the set, so no change is made.
	fmt.Println(obj.PopSmallest()) // return 1, since 1 is the smallest number, and remove it from the set.
	fmt.Println(obj.PopSmallest()) // return 2, and remove it from the set.
	fmt.Println(obj.PopSmallest()) // return 3, and remove it from the set.
	obj.AddBack(1)                 // 1 is added back to the set.
	fmt.Println(obj.PopSmallest()) // return 1, since 1 was added back to the set and
	fmt.Println(obj.PopSmallest()) // return 4, and remove it from the set.
	fmt.Println(obj.PopSmallest()) // return 5, and remove it from the set.
}
