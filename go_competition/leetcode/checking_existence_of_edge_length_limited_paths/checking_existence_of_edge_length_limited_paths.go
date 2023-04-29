package checking_existence_of_edge_length_limited_paths

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

func union(sets []int, s1 int, s2 int) {
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
	}
}

func distanceLimitedPathsExist(n int, edgeList [][]int, queries [][]int) []bool {
	answers := []bool{}
	for q := 0; q < len(queries); q++ {
		queries[q] = append(queries[q], q)
		answers = append(answers, false)
	}
	sort.Slice(edgeList, func(i, j int) bool {
		return edgeList[i][2] < edgeList[j][2]
	})
	sort.Slice(queries, func(i, j int) bool {
		return queries[i][2] < queries[j][2]
	})
	sets := []int{}
	for i := 0; i < n; i++ {
		sets = append(sets, -1)
	}
	u := 0
	for q := 0; q < len(queries); q++ {
		for u < len(edgeList) && edgeList[u][2] < queries[q][2] {
			union(sets, edgeList[u][0], edgeList[u][1])
			u = u + 1
		}
		answers[queries[q][3]] = find(sets, queries[q][0]) == find(sets, queries[q][1])
	}
	return answers
}

func Main() {
	answers := distanceLimitedPathsExist(3, [][]int{[]int{0, 1, 2}, []int{1, 2, 4}, []int{2, 0, 8}, []int{1, 0, 16}}, [][]int{[]int{0, 1, 2}, []int{0, 2, 5}})
	for i := 0; i < len(answers); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(answers[i])
	}
	fmt.Println()
}
