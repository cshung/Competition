package minimum_number_of_vertices_to_reach_all_nodes

import (
	"fmt"
)

func findSmallestSetOfVertices(n int, edges [][]int) []int {
	indegree := make([]int, n)
	for e := 0; e < len(edges); e++ {
		indegree[edges[e][1]]++
	}
	answers := []int{}
	for v := 0; v < n; v++ {
		if indegree[v] == 0 {
			answers = append(answers, v)
		}
	}
	return answers
}

func Main() {
	answers := findSmallestSetOfVertices(6, [][]int{[]int{0, 1}, []int{0, 2}, []int{2, 5}, []int{3, 4}, []int{4, 2}})
	for i := 0; i < len(answers); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(answers[i])
	}
	fmt.Println()
}
