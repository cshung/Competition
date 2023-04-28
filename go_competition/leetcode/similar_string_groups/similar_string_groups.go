package similar_string_groups

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

func union(sets []int, i int, j int) {
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

func numSimilarGroups(strs []string) int {
	n := len(strs)
	m := len(strs[0])
	sets := []int{}
	for i := 0; i < n; i++ {
		sets = append(sets, -1)
	}
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			si := find(sets, i)
			sj := find(sets, j)
			if si != sj {
				mismatch := 0
				for k := 0; k < m; k++ {
					if strs[i][k] != strs[j][k] {
						mismatch = mismatch + 1
						if mismatch > 2 {
							break
						}
					}
				}
				if mismatch <= 2 {
					union(sets, si, sj)
				}
			}
		}
	}
	counts := 0
	for i := 0; i < n; i++ {
		if sets[i] < 0 {
			counts = counts + 1
		}
	}
	return counts
}

func Main() {
	answer := numSimilarGroups([]string{"tars", "rats", "arts", "star"})
	fmt.Println(answer)
}
