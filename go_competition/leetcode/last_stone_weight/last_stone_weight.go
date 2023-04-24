package last_stone_weight

import (
	"container/heap"
	"fmt"
)

// An IntHeap is a min-heap of ints.
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x interface{}) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, x.(int))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func lastStoneWeight(stones []int) int {
	h := &IntHeap{}
	heap.Init(h)
	for i := 0; i < len(stones); i++ {
		heap.Push(h, -stones[i])
	}
	for h.Len() > 1 {
		biggest := heap.Pop(h).(int)
		second := heap.Pop(h).(int)
		if second > biggest {
			heap.Push(h, biggest-second)
		}
	}
	if h.Len() == 0 {
		return 0
	} else {
		return (0 - heap.Pop(h).(int))
	}
}

func Main() {
	answer := lastStoneWeight([]int{2, 7, 4, 1, 8, 1})
	fmt.Println(answer)
}
