package time_needed_to_inform_all_employees

import (
	"fmt"
)

func dfs(v int, adj [][]int, informTime []int) int {
	if len(adj[v]) == 0 {
		return 0
	} else {
		m := 0
		for i := 0; i < len(adj[v]); i++ {
			dfs_v := dfs(adj[v][i], adj, informTime)
			if dfs_v > m {
				m = dfs_v
			}
		}
		return m + informTime[v]
	}
}

func numOfMinutes(n int, headID int, manager []int, informTime []int) int {
	adj := make([][]int, n)
	for i := 0; i < n; i++ {
		adj[i] = []int{}
	}
	head := -1
	for i := 0; i < n; i++ {
		if manager[i] == -1 {
			head = i
		} else {
			adj[manager[i]] = append(adj[manager[i]], i)
		}
	}
	return dfs(head, adj, informTime)
}

func Main() {
	answer := numOfMinutes(1, 0, []int{-1}, []int{0})
	fmt.Println(answer)
}
