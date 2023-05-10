package spiral_matrix_ii

import (
	"fmt"
)

func generateMatrix(n int) [][]int {
	matrix := make([][]int, n)
	for i := 0; i < n; i++ {
		matrix[i] = make([]int, n)
	}
	r := 0
	c := 0
	m := 0
	r_min := 0
	r_max := len(matrix) - 1
	c_min := 0
	c_max := len(matrix[0]) - 1
	k := 1
	for r_max >= r_min && c_max >= c_min {
		om := m
		matrix[r][c] = k
		k = k + 1
		if m == 0 {
			if c == c_max {
				r_min = r_min + 1
				m = 1
			} else {
				c = c + 1
			}
		} else if m == 1 {
			if r == r_max {
				c_max = c_max - 1
				m = 2
			} else {
				r = r + 1
			}
		} else if m == 2 {
			if c == c_min {
				r_max = r_max - 1
				m = 3
			} else {
				c = c - 1
			}
		} else {
			if r == r_min {
				c_min = c_min + 1
				m = 0
			} else {
				r = r - 1
			}
		}
		if m != om {
			k = k - 1
		}
	}
	matrix[r][c] = k
	return matrix
}

func Main() {
	answers := generateMatrix(3)
	for i := 0; i < len(answers); i++ {
		for j := 0; j < len(answers[i]); j++ {
			if j > 0 {
				fmt.Print(" ")
			}
			fmt.Print(answers[i][j])
		}
		fmt.Println()
	}

}
