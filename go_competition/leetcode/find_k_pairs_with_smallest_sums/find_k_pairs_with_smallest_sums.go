package find_k_pairs_with_smallest_sums

import (
	"container/heap"
	"fmt"
)

type Pair struct {
	first  int
	second int
	sum    int
}

type PairHeap []Pair

func (h PairHeap) Len() int { return len(h) }
func (h PairHeap) Less(i, j int) bool {
	return h[i].sum < h[j].sum || ((h[i].sum == h[j].sum) && (h[i].first < h[j].first)) || ((h[i].sum == h[j].sum) && (h[i].first == h[j].first) && (h[i].second < h[j].second))
}
func (h PairHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }

func (h *PairHeap) Push(x interface{}) {
	*h = append(*h, x.(Pair))
}

func (h *PairHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func kSmallestPairs(nums1 []int, nums2 []int, k int) [][]int {
	next1 := make([]int, len(nums1))
	next2 := make([]int, len(nums2))
	next1[0] = 1
	next2[0] = 1
	pairs := make(PairHeap, 0)
	heap.Push(&pairs, Pair{0, 0, nums1[0] + nums2[0]})
	answers := [][]int{}
	for i := 0; (i < k) && (len(pairs) > 0); i++ {
		pair := heap.Pop(&pairs).(Pair)
		if (next1[pair.first] == pair.second+1) && (pair.second+1 < len(nums2)) {
			heap.Push(&pairs, Pair{pair.first, pair.second + 1, nums1[pair.first] + nums2[pair.second+1]})
			next1[pair.first] = pair.second + 2
			next2[pair.second+1] = pair.first + 1
		}
		if (next2[pair.second] == pair.first+1) && (pair.first+1 < len(nums1)) {
			heap.Push(&pairs, Pair{pair.first + 1, pair.second, nums1[pair.first+1] + nums2[pair.second]})
			next1[pair.first+1] = pair.second + 1
			next2[pair.second] = pair.first + 2
		}
		answers = append(answers, []int{nums1[pair.first], nums2[pair.second]})
	}
	return answers
}

func Main() {
	answer := kSmallestPairs([]int{1, 7, 11}, []int{2, 4, 6}, 3)
	fmt.Println(answer)
}
