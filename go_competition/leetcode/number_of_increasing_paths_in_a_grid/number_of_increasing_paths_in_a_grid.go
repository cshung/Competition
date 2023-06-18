package number_of_increasing_paths_in_a_grid

import (
	"fmt"
)

func addEdge(adj map[int][]int, src int, dst int) {
	dsts, ok := adj[src]
	if !ok {
		dsts = []int{}
	}
	dsts = append(dsts, dst)
	adj[src] = dsts
}

func dfs(v int, adj map[int][]int, counts []int) {
	answer := 1
	neighbors, ok := adj[v]
	if ok {
		for i := 0; i < len(neighbors); i++ {
			neighbor := neighbors[i]
			if counts[neighbor] == 0 {
				dfs(neighbor, adj, counts)
			}
			answer += counts[neighbor]
			answer = answer % 1000000007
		}
	}
	counts[v] = answer
}

func countPaths(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])
	a := m * n
	counts := make([]int, a)
	adj := make(map[int][]int)
	for r := 0; r < m; r++ {
		for c := 0; c < n; c++ {
			if c > 0 && grid[r][c] < grid[r][c-1] {
				addEdge(adj, r*n+c, r*n+c-1)
			}
			if c < n-1 && grid[r][c] < grid[r][c+1] {
				addEdge(adj, r*n+c, r*n+c+1)
			}
			if r > 0 && grid[r][c] < grid[r-1][c] {
				addEdge(adj, r*n+c, r*n-n+c)
			}
			if r < m-1 && grid[r][c] < grid[r+1][c] {
				addEdge(adj, r*n+c, r*n+n+c)
			}
		}
	}
	answer := 0
	for i := 0; i < a; i++ {
		dfs(i, adj, counts)
		answer += counts[i]
		answer = answer % 1000000007
	}

	return answer
}

func Main() {
	// answer := countPaths([][]int{[]int{1}, []int{2}})
	answer := countPaths([][]int{[]int{1, 1}, []int{3, 4}})
	fmt.Println(answer)
}
