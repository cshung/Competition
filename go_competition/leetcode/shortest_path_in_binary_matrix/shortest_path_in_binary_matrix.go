package shortest_path_in_binary_matrix

import (
	"fmt"
)

func shortestPathBinaryMatrix(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])
	if grid[0][0] != 0 {
		return -1
	}
	bfs := []int{}
	dis := []int{}
	grid[0][0] = 2
	bfs = append(bfs, 0)
	dis = append(dis, 0)
	for len(bfs) > 0 {
		visiting := bfs[0]
		bfs = bfs[1:]
		distance := dis[0]
		dis = dis[1:]
		vr := visiting / n
		vc := visiting % n

		for dr := -1; dr <= 1; dr++ {
			for dc := -1; dc <= 1; dc++ {
				nr := vr + dr
				nc := vc + dc
				if 0 <= nr && nr < m && 0 <= nc && nc < n && grid[nr][nc] == 0 {
					grid[nr][nc] = 2
					if nr == m-1 && nc == n-1 {
						return distance + 1
					}
					bfs = append(bfs, nr*n+nc)
					dis = append(dis, distance+1)
				}
			}
		}
	}
	return -1
}

func Main() {
	answer := shortestPathBinaryMatrix([][]int{[]int{0, 1}, []int{1, 0}})
	fmt.Println(answer)
}
