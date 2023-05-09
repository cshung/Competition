package spiral_matrix

import (
	"fmt"
)

func spiralOrder(matrix [][]int) []int {
	r := 0
	c := 0
	m := 0
	r_min := 0
	r_max := len(matrix) - 1
	c_min := 0
	c_max := len(matrix[0]) - 1
	answers := []int{}
	for r_max >= r_min && c_max >= c_min {
		answer := matrix[r][c]
		om := m
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
		if m == om {
			answers = append(answers, answer)
		}
	}
	answers = append(answers, matrix[r][c])
	return answers
}

func Main() {
	answers := spiralOrder([][]int{[]int{1, 2, 3}, []int{4, 5, 6}, []int{7, 8, 9}})
	for i := 0; i < len(answers); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(answers[i])
	}
	fmt.Println()
}
