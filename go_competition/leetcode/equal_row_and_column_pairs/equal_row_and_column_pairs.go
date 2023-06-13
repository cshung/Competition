package equal_row_and_column_pairs

import (
	"fmt"
	"strconv"
	"strings"
)

func equalPairs(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])
	rows := make(map[string][]int)
	for r := 0; r < m; r++ {
		rss := []string{}
		for c := 0; c < n; c++ {
			rss = append(rss, strconv.Itoa(grid[r][c]))
		}
		rs := strings.Join(rss, ",")
		mapped, ok := rows[rs]
		if !ok {
			mapped = []int{}
		}
		rows[rs] = append(mapped, r)
	}
	answer := 0
	for c := 0; c < n; c++ {
		css := []string{}
		for r := 0; r < m; r++ {
			css = append(css, strconv.Itoa(grid[r][c]))
		}
		cs := strings.Join(css, ",")
		mapped, ok := rows[cs]
		if ok {
			answer += len(mapped)
		}
	}
	return answer
}

func Main() {
	answer := equalPairs([][]int{[]int{3, 2, 1}, []int{1, 7, 6}, []int{2, 7, 7}})
	fmt.Println(answer)
}
