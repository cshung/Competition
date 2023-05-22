package shortest_bridge

import (
	"fmt"
)

type point struct {
	r int
	c int
	d int
}

func shortestBridge(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])
	done := false
	for r := 0; r < m && !done; r++ {
		for c := 0; c < n && !done; c++ {
			if grid[r][c] == 1 {
				bfs := []point{}
				bfs = append(bfs, point{r: r, c: c, d: 0})
				grid[r][c] = 2
				for len(bfs) > 0 {
					p := bfs[0]
					bfs = bfs[1:]
					pr := p.r
					pc := p.c
					if pr > 0 && grid[pr-1][pc] == 1 {
						grid[pr-1][pc] = 2
						bfs = append(bfs, point{r: pr - 1, c: pc, d: 0})
					}
					if pr+1 < m && grid[pr+1][pc] == 1 {
						grid[pr+1][pc] = 2
						bfs = append(bfs, point{r: pr + 1, c: pc, d: 0})
					}
					if pc > 0 && grid[pr][pc-1] == 1 {
						grid[pr][pc-1] = 2
						bfs = append(bfs, point{r: pr, c: pc - 1, d: 0})
					}
					if pc+1 < n && grid[pr][pc+1] == 1 {
						grid[pr][pc+1] = 2
						bfs = append(bfs, point{r: pr, c: pc + 1, d: 0})
					}
				}
				done = true
			}
		}
	}
	bfs := []point{}
	for r := 0; r < m; r++ {
		for c := 0; c < n; c++ {
			if grid[r][c] == 2 {
				if r > 0 && grid[r-1][c] == 0 {
					bfs = append(bfs, point{r: r - 1, c: c, d: 1})
					grid[r-1][c] = 3
				}
				if r+1 < m && grid[r+1][c] == 0 {
					bfs = append(bfs, point{r: r + 1, c: c, d: 1})
					grid[r+1][c] = 3
				}
				if c > 0 && grid[r][c-1] == 0 {
					bfs = append(bfs, point{r: r, c: c - 1, d: 1})
					grid[r][c-1] = 3
				}
				if c+1 < n && grid[r][c+1] == 0 {
					bfs = append(bfs, point{r: r, c: c + 1, d: 1})
					grid[r][c+1] = 3
				}
			}
		}
	}

	for len(bfs) > 0 {
		p := bfs[0]
		bfs = bfs[1:]
		pr := p.r
		pc := p.c
		pd := p.d
		if pr > 0 && grid[pr-1][pc] < 2 {
			if grid[pr-1][pc] == 1 {
				return pd
			}
			grid[pr-1][pc] = 3
			bfs = append(bfs, point{r: pr - 1, c: pc, d: pd + 1})
		}
		if pr+1 < m && grid[pr+1][pc] < 2 {
			if grid[pr+1][pc] == 1 {
				return pd
			}
			grid[pr+1][pc] = 3
			bfs = append(bfs, point{r: pr + 1, c: pc, d: pd + 1})
		}
		if pc > 0 && grid[pr][pc-1] < 2 {
			if grid[pr][pc-1] == 1 {
				return pd
			}
			grid[pr][pc-1] = 3
			bfs = append(bfs, point{r: pr, c: pc - 1, d: pd + 1})
		}
		if pc+1 < n && grid[pr][pc+1] < 2 {
			if grid[pr][pc+1] == 1 {
				return pd
			}
			grid[pr][pc+1] = 3
			bfs = append(bfs, point{r: pr, c: pc + 1, d: pd + 1})
		}
	}
	return -1
}

func Main() {
	answer := shortestBridge([][]int{[]int{0, 1}, []int{1, 0}})
	fmt.Println(answer)
}
