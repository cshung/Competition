package maximum_number_of_achievable_transfer_requests

import (
	"fmt"
)

func maximumRequests(n int, requests [][]int) int {
	cost := make([]int, n+2)
	next := make([]int, n+2)
	pred := make([]int, n+2)
	flip := make([]bool, len(requests))
	infinite := 100
	count := 0
	for {
		for i := 0; i < n+2; i++ {
			cost[i] = infinite
		}
		cost[n] = 0
		for round := 0; round < n+2; round++ {
			for i := 0; i < n+2; i++ {
				next[i] = cost[i]
			}
			for s := 0; s < n; s++ {
				if cost[n] != infinite && cost[s] > cost[n] {
					next[s] = cost[n]
					pred[s] = n
				}
			}
			for e := 0; e < len(requests); e++ {
				src := requests[e][0]
				dst := requests[e][1]
				weight := -1
				if flip[e] {
					src, dst, weight = dst, src, -weight
				}
				if cost[src] != infinite && cost[dst] > cost[src]+weight {
					next[dst] = cost[src] + weight
					pred[dst] = e
				}
			}
			for s := 0; s < n; s++ {
				if cost[s] != infinite && cost[n+1] > cost[s] {
					next[n+1] = cost[s]
					pred[n+1] = s
				}
			}
			cost, next = next, cost
		}
		found := false
		node := 0
		for i := 0; i < n+1; i++ {
			if cost[i] < next[i] {
				found = true
				node = i
			}
		}
		if !found && cost[n+1] < next[n+1] {
			found = true
			node = pred[n+1]
		}
		if found {
			cur := node
			seen := make([]int, n)
			edgeStack := []int{}
			for {
				seen[cur] = 1
				e := pred[cur]
				src := requests[e][0]
				dst := requests[e][1]
				if flip[e] {
					src, dst = dst, src
				}
				edgeStack = append(edgeStack, e)
				cur = src
				if seen[cur] == 1 {
					for i := len(edgeStack) - 1; i >= 0; i-- {
						e := edgeStack[i]
						src := requests[e][0]
						dst := requests[e][1]
						if flip[e] {
							src, dst = dst, src
							count = count - 1
						} else {
							count = count + 1
						}
						flip[e] = !flip[e]
						if dst == cur {
							break
						}
					}
					break
				}
			}
		} else {
			break
		}
	}

	return count
}

func Main() {
	answer := maximumRequests(5, [][]int{[]int{0, 1}, []int{1, 0}, []int{0, 1}, []int{1, 2}, []int{2, 0}, []int{3, 4}})
	fmt.Println(answer)
}
