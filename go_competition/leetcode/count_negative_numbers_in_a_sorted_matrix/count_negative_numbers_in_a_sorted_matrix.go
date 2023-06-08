package count_negative_numbers_in_a_sorted_matrix

import (
	"fmt"
)

func countNegatives(grid [][]int) int {
	h := len(grid)
	w := len(grid[0])
	r := h - 1
	count := 0
	for c := 0; c < w; c++ {
		for r != -1 && grid[r][c] < 0 {
			r--
		}
		count += (r + 1)
	}
	return h*w - count
}

func Main() {
	answer := countNegatives([][]int{[]int{4, 3, 2, -1}, []int{3, 2, 1, -1}, []int{1, 1, -1, -2}, []int{-1, -1, -2, -3}})
	fmt.Println(answer)
}
