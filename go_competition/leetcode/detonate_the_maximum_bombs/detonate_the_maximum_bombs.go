package detonate_the_maximum_bombs

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func dfs(adj [][]int, v int, visited []bool) int {
	visited[v] = true
	s := 1
	for i := 0; i < len(adj[v]); i++ {
		neighbor := adj[v][i]
		if !visited[neighbor] {
			s = s + dfs(adj, neighbor, visited)
		}
	}
	return s
}

func maximumDetonation(bombs [][]int) int {
	n := len(bombs)
	adj := [][]int{}

	for i := 0; i < n; i++ {
		adj = append(adj, []int{})
		ix := bombs[i][0]
		iy := bombs[i][1]
		r := bombs[i][2]
		for j := 0; j < n; j++ {
			if i != j {
				jx := bombs[j][0]
				jy := bombs[j][1]
				dx := ix - jx
				dy := iy - jy
				if dx*dx+dy*dy <= r*r {
					adj[i] = append(adj[i], j)
				}
			}
		}
	}
	answer := 0
	for i := 0; i < n; i++ {
		visited := make([]bool, n)
		answer = max(answer, dfs(adj, i, visited))
	}

	return answer
}

func Main() {
	answer := maximumDetonation([][]int{[]int{2, 1, 3}, []int{6, 1, 4}})
	fmt.Println(answer)
}
