package matrix_diagonal_sum

import (
	"fmt"
)

func diagonalSum(mat [][]int) int {
	n := len(mat)
	s := 0
	for i := 0; i < n; i++ {
		s = s + mat[i][i]
		s = s + mat[i][n-i-1]
	}
	if n%2 == 1 {
		s = s - mat[n/2][n/2]
	}
	return s
}

func Main() {
	answer := diagonalSum([][]int{[]int{1, 2, 3}, []int{4, 5, 6}, []int{7, 8, 9}})
	fmt.Println(answer)
}
