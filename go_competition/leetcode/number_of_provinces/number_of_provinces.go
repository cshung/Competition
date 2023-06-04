package number_of_provinces

import (
	"fmt"
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

func findCircleNum(isConnected [][]int) int {
	n := len(isConnected)
	sets := make([]int, n)
	for i := 0; i < n; i++ {
		sets[i] = -1
	}
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			if isConnected[i][j] == 1 {
				union(sets, i, j)
			}
		}
	}
	answer := 0
	for i := 0; i < n; i++ {
		if sets[i] < 0 {
			answer++
		}
	}
	return answer
}

func Main() {
	answer := findCircleNum([][]int{[]int{1, 1, 0}, []int{1, 1, 0}, []int{0, 0, 1}})
	fmt.Println(answer)
}
