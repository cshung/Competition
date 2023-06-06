package check_if_it_is_a_straight_line

import (
	"fmt"
)

func checkStraightLine(coordinates [][]int) bool {
	x0 := coordinates[0][0]
	y0 := coordinates[0][1]
	x1 := coordinates[1][0]
	y1 := coordinates[1][1]
	nx := y1 - y0
	ny := x0 - x1
	for i := 2; i < len(coordinates); i++ {
		xi := coordinates[i][0]
		yi := coordinates[i][1]
		dx := xi - x0
		dy := yi - y0
		if dx*nx+dy*ny != 0 {
			return false
		}
	}
	return true
}

func Main() {
	answer := checkStraightLine([][]int{[]int{1, 2}, []int{2, 3}, []int{3, 4}, []int{4, 5}, []int{5, 6}, []int{6, 7}})
	fmt.Println(answer)
}
