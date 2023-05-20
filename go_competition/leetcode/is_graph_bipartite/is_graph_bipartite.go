package is_graph_bipartite

import (
	"fmt"
)

func dfs(v int, color int, graph [][]int, colors []int) bool {
	colors[v] = color
	next_color := 3 - color
	for i := 0; i < len(graph[v]); i++ {
		n := graph[v][i]

		if colors[n] == 0 {
			if !dfs(n, next_color, graph, colors) {
				return false
			}
		} else if colors[n] != next_color {
			return false
		}
	}
	return true
}

func isBipartite(graph [][]int) bool {
	n := len(graph)
	colors := make([]int, n)
	for i := 0; i < n; i++ {
		if colors[i] == 0 {
			if !dfs(i, 1, graph, colors) {
				return false
			}
		}
	}
	return true
}

func Main() {
	answer := isBipartite([][]int{[]int{1, 2, 3}, []int{0, 2}, []int{0, 1, 3}, []int{0, 2}})
	fmt.Println(answer)
}
