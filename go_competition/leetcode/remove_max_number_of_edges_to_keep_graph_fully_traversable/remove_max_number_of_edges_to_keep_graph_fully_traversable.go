package remove_max_number_of_edges_to_keep_graph_fully_traversable

import (
	"fmt"
	"sort"
)

func find(sets []int, i int) int {
	if sets[i] < 0 {
		return i
	} else {
		sets[i] = find(sets, sets[i])
		return sets[i]
	}
}

func union(sets []int, s1 int, s2 int) bool {
	i := find(sets, s1)
	j := find(sets, s2)
	if i != j {
		neg_size_i := sets[i]
		neg_size_j := sets[j]
		if neg_size_i > neg_size_j {
			sets[i] = j
			sets[j] = neg_size_i + neg_size_j
		} else {
			sets[j] = i
			sets[i] = neg_size_i + neg_size_j
		}
		return true
	} else {
		return false
	}
}

func maxNumEdgesToRemove(n int, edges [][]int) int {
	sort.Slice(edges, func(i, j int) bool {
		return edges[i][0] > edges[j][0]
	})
	alice := []int{}
	bob := []int{}
	for i := 0; i < n; i++ {
		alice = append(alice, -1)
		bob = append(bob, -1)
	}
	alice_count := n
	bob_count := n
	drop_count := 0
	for i := 0; i < len(edges); i++ {
		color := edges[i][0]
		from := edges[i][1] - 1
		to := edges[i][2] - 1
		dropped := true
		if color == 1 || color == 3 {
			if union(alice, from, to) {
				alice_count = alice_count - 1
				dropped = false
			}
		}
		if color == 2 || color == 3 {
			if union(bob, from, to) {
				bob_count = bob_count - 1
				dropped = false
			}
		}
		if dropped {
			drop_count = drop_count + 1
		}
	}
	if alice_count == 1 && bob_count == 1 {
		return drop_count
	} else {
		return -1
	}
}

func Main() {
	answer := maxNumEdgesToRemove(4, [][]int{[]int{3, 1, 2}, []int{3, 2, 3}, []int{1, 1, 3}, []int{1, 2, 4}, []int{1, 1, 2}, []int{2, 3, 4}})
	fmt.Println(answer)
}
