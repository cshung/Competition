package shortest_path_to_get_all_keys

import (
	"fmt"
)

type myarr [57600]int

var heapNode [57600]int
var nodeHeap [57600]int
var costs [57600]int
var parents [57600]int
var size int

func swap(h1 int, h2 int) {
	n1 := heapNode[h1]
	n2 := heapNode[h2]
	heapNode[h1] = n2
	heapNode[h2] = n1
	nodeHeap[n1] = h2
	nodeHeap[n2] = h1
}

func bubbleUp(h int) {
	for h > 0 {
		p := (h+1)/2 - 1
		if costs[heapNode[h]] < costs[heapNode[p]] {
			swap(h, p)
			h = p
		} else {
			break
		}
	}
}

func stoneDown(h int) {

	for h < size-1 {

		rc := (h + 1) * 2
		lc := rc - 1
		if rc < size {
			if costs[heapNode[lc]] < costs[heapNode[h]] && costs[heapNode[lc]] <= costs[heapNode[rc]] {
				swap(h, lc)
				h = lc
			} else if costs[heapNode[rc]] < costs[heapNode[h]] && costs[heapNode[rc]] <= costs[heapNode[lc]] {
				swap(h, rc)
				h = rc
			} else {
				break
			}
		} else if lc < size {
			if costs[heapNode[lc]] < costs[heapNode[h]] {
				swap(h, lc)
				h = lc
			} else {
				break
			}
		} else {
			break
		}
	}
}

func shortestPathAllKeys(grid []string) int {

	m := len(grid)
	n := len(grid[0])

	for i := 0; i < 57600; i++ {
		heapNode[i] = -1
		nodeHeap[i] = -1
		parents[i] = -1
		costs[i] = -1.0
	}

	types := make(map[byte]int)
	sr := -1
	sc := -1
	for r := 0; r < m; r++ {
		for c := 0; c < n; c++ {
			g := grid[r][c]
			if g == "@"[0] {
				sr = r
				sc = c
			}
			if "a"[0] <= g && g <= "z"[0] {
				next_type_id := len(types)/2 + 1
				types[g] = -next_type_id
				types[g+"A"[0]-"a"[0]] = next_type_id
			}
		}
	}

	wall := 7
	empty := 8
	allKeyCount := len(types) / 2
	types["#"[0]] = wall
	types["@"[0]] = empty
	types["."[0]] = empty

	start := sr*30 + sc

	size = 1
	heapNode[0] = start
	nodeHeap[start] = 0
	costs[start] = 0.0
	parents[start] = -1

	drs := []int{1, -1, 0, 0}
	dcs := []int{0, 0, 1, -1}
	keys := make([]int, 6)

	for size > 0 {
		srcNode := heapNode[0]
		nodeHeap[srcNode] = -2
		size = size - 1

		if size > 0 {
			heapNode[0] = heapNode[size]
			nodeHeap[heapNode[0]] = 0
			heapNode[size] = -1
			stoneDown(0)
		} else {
			heapNode[0] = -1
		}
		temp := srcNode
		srcCol := temp % 30
		temp = temp / 30
		srcRow := temp % 30
		temp = temp / 30
		for i := 0; i < 6; i++ {
			keys[i] = temp % 2
			temp = temp / 2
		}

		for d := 0; d < 4; d++ {
			dr := drs[d]
			dc := dcs[d]
			dstRow := srcRow + dr
			dstCol := srcCol + dc
			if dstRow >= 0 && dstRow < m && dstCol >= 0 && dstCol < n {
				dstCell := grid[dstRow][dstCol]
				dstType := types[dstCell]
				if dstType == empty || dstType < 0 || (dstType != wall && keys[dstType-1] > 0) {

					keyWas := 0
					if dstType < 0 {
						keyWas = keys[-1-dstType]
						keys[-1-dstType] = 1
					}

					dstNode := 0
					keyCount := 0
					for i := 0; i < 6; i++ {
						if keys[6-i-1] > 0 {
							keyCount += 1
						}
						dstNode += keys[6-i-1]
						dstNode = dstNode * 2
					}
					dstNode = dstNode * 15
					dstNode = dstNode + dstRow
					dstNode = dstNode * 30
					dstNode = dstNode + dstCol

					if keyCount == allKeyCount {
						return costs[srcNode] + 1
					}

					dstHeap := nodeHeap[dstNode]
					newCost := costs[srcNode] + 1
					if dstHeap == -1 {
						heapNode[size] = dstNode
						nodeHeap[dstNode] = size
						size = size + 1
						costs[dstNode] = newCost
						bubbleUp(size - 1)
					} else {
						if newCost < costs[dstNode] {
							costs[dstNode] = newCost
							bubbleUp(dstHeap)
						}
					}

					if dstType < 0 {
						keys[-1-dstType] = keyWas
					}
				}
			}
		}
	}

	return -1
}

func Main() {
	answer := shortestPathAllKeys([]string{"@.a..", "###.#", "b.A.B"})
	fmt.Println(answer)
}
