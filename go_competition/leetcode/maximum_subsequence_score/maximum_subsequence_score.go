package maximum_subsequence_score

import (
	"container/heap"
	"fmt"
	"sort"
)

type IntHeap []int64

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x interface{}) {
	*h = append(*h, x.(int64))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func maxScore(nums1 []int, nums2 []int, k int) int64 {
	n := len(nums1)
	indices := make([]int, n)
	for i := 0; i < n; i++ {
		indices[i] = i
	}
	sort.Slice(indices, func(i, j int) bool {
		return nums2[indices[i]] > nums2[indices[j]]
	})
	sum := int64(0)
	top := IntHeap{}
	for i := 0; i < k-1; i++ {
		v := int64(nums1[indices[i]])
		sum = sum + v
		heap.Push(&top, v)
	}
	answer := int64(-1)

	for i := k - 1; i < n; i++ {
		v := int64(nums1[indices[i]])
		sum = sum + v
		candidate := sum * int64(nums2[indices[i]])
		if candidate > answer {
			answer = candidate
		}
		heap.Push(&top, v)
		r := heap.Pop(&top).(int64)
		sum = sum - r
	}

	return answer
}

func Main() {
	answer := maxScore([]int{1, 3, 3, 2}, []int{2, 1, 3, 4}, 3)
	fmt.Println(answer)
}
