package minimum_cost_to_cut_a_stick

import (
	"fmt"
	"sort"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func minCost(n int, cuts []int) int {
	cuts = append(cuts, 0)
	cuts = append(cuts, n)
	sort.Ints(cuts)
	p := len(cuts) - 1
	// answers[i][j] is the minCost of cutting the piece [cut[i] - cut[i + j + 1]]
	answers := [][]int{}
	for i := 0; i < p; i++ {
		answers = append(answers, make([]int, p-i))
	}
	for l := 2; l <= p; l++ {
		for i := 0; i+l <= p; i++ {
			answers[i][l-1] = answers[i][0] + answers[i+1][l-2]
			for c := 1; c < l-1; c++ {
				answers[i][l-1] = min(answers[i][l-1], answers[i][c]+answers[i+c+1][l-c-2])
			}
			answers[i][l-1] += (cuts[i+l] - cuts[i])
		}
	}
	return answers[0][p-1]
}

func Main() {
	answer := minCost(7, []int{1, 3, 4, 5})
	fmt.Println(answer)
}
