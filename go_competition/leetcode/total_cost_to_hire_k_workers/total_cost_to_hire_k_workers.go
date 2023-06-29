package total_cost_to_hire_k_workers

import (
	"container/heap"
	"fmt"
)

type Worker struct {
	cost  int
	index int
}

type WorkerHeap []Worker

func (h WorkerHeap) Len() int { return len(h) }

func (h WorkerHeap) Less(i, j int) bool {
	return h[i].cost < h[j].cost || (h[i].cost == h[j].cost && h[i].index < h[j].index)
}

func (h WorkerHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }

func (h *WorkerHeap) Push(x interface{}) {
	*h = append(*h, x.(Worker))
}

func (h *WorkerHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func totalCost(costs []int, k int, candidates int) int64 {
	n := len(costs)
	le := 0
	re := n - 1
	pool := make(WorkerHeap, 0)
	for i := 0; i < candidates; i++ {
		if le <= re {
			heap.Push(&pool, Worker{costs[le], le})
			le = le + 1
		}
	}
	for i := 0; i < candidates; i++ {
		if le <= re {
			heap.Push(&pool, Worker{costs[re], re})
			re = re - 1
		}
	}
	answer := int64(0)
	for i := 0; i < k; i++ {
		chosen := heap.Pop(&pool).(Worker)
		answer = answer + int64(chosen.cost)
		if le <= re {
			if chosen.index < le {
				heap.Push(&pool, Worker{costs[le], le})
				le = le + 1
			} else {
				heap.Push(&pool, Worker{costs[re], re})
				re = re - 1
			}
		}
	}
	return answer
}

func Main() {
	answer := totalCost([]int{17, 12, 10, 2, 7, 2, 11, 20, 8}, 3, 4)
	fmt.Println(answer)
}
