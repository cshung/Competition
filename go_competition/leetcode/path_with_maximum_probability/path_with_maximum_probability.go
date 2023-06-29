package path_with_maximum_probability

import (
	"fmt"
	"math"
)

type Edge struct {
	dst    int
	weight float64
}

func swap(heapNode []int, nodeHeap []int, h1 int, h2 int) {
	n1 := heapNode[h1]
	n2 := heapNode[h2]
	heapNode[h1] = n2
	heapNode[h2] = n1
	nodeHeap[n1] = h2
	nodeHeap[n2] = h1
}

func bubbleUp(heapNode []int, nodeHeap []int, costs []float64, size int, h int) {
	for h > 0 {
		p := (h+1)/2 - 1
		if costs[heapNode[h]] < costs[heapNode[p]] {
			swap(heapNode, nodeHeap, h, p)
			h = p
		} else {
			break
		}
	}
}

func stoneDown(heapNode []int, nodeHeap []int, costs []float64, size int, h int) {
	for h < size-1 {
		rc := (h + 1) * 2
		lc := rc - 1
		if rc < size {
			if costs[heapNode[lc]] < costs[heapNode[h]] && costs[heapNode[lc]] <= costs[heapNode[rc]] {
				swap(heapNode, nodeHeap, h, lc)
				h = lc
			} else if costs[heapNode[rc]] < costs[heapNode[h]] && costs[heapNode[rc]] <= costs[heapNode[lc]] {
				swap(heapNode, nodeHeap, h, rc)
				h = rc
			} else {
				break
			}
		} else if lc < size {
			if costs[heapNode[lc]] < costs[heapNode[h]] {
				swap(heapNode, nodeHeap, h, lc)
				h = lc
			} else {
				break
			}
		} else {
			break
		}
	}
}

func maxProbability(n int, edges [][]int, succProb []float64, start int, end int) float64 {
	adj := make([][]Edge, n)
	for i := 0; i < n; i++ {
		adj[i] = []Edge{}
	}
	for i := 0; i < len(edges); i++ {
		src := edges[i][0]
		dst := edges[i][1]
		weight := -math.Log(succProb[i])
		adj[src] = append(adj[src], Edge{dst, weight})
		adj[dst] = append(adj[dst], Edge{src, weight})
	}

	heapNode := make([]int, n)
	nodeHeap := make([]int, n)
	costs := make([]float64, n)
	parents := make([]int, n)

	for i := 0; i < n; i++ {
		heapNode[i] = -1
		nodeHeap[i] = -1
		parents[i] = -1
		costs[i] = -1.0
	}

	size := 1
	heapNode[0] = start
	nodeHeap[start] = 0
	costs[start] = 0.0
	parents[start] = -1

	for size > 0 {
		srcNode := heapNode[0]
		nodeHeap[srcNode] = -2
		size = size - 1
		if size > 0 {
			heapNode[0] = heapNode[size]
			nodeHeap[heapNode[0]] = 0
			heapNode[size] = -1
			stoneDown(heapNode, nodeHeap, costs, size, 0)
		} else {
			heapNode[0] = -1
		}
		edges := adj[srcNode]
		for edgeIndex := range edges {
			edge := edges[edgeIndex]
			dstNode := edge.dst
			dstHeap := nodeHeap[dstNode]
			newCost := costs[srcNode] + edge.weight
			if dstHeap == -1 {
				heapNode[size] = dstNode
				nodeHeap[dstNode] = size
				size = size + 1
				costs[dstNode] = newCost
				bubbleUp(heapNode, nodeHeap, costs, size, size-1)
			} else {
				if newCost < costs[dstNode] {
					costs[dstNode] = newCost
					bubbleUp(heapNode, nodeHeap, costs, size, dstHeap)
				} else {
				}
			}
		}
	}

	if costs[end] < 0 {
		return 0
	} else {
		return 1.0 / math.Exp(costs[end])
	}
}

func Main() {
	answer := maxProbability(3, [][]int{[]int{0, 1}, []int{1, 2}, []int{0, 2}}, []float64{0.5, 0.5, 0.2}, 0, 2)
	fmt.Println(answer)
}
