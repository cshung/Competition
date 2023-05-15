package paint_house_ii

import (
	"fmt"
)

func minCostII(costs [][]int) int {
	n := len(costs)
	k := len(costs[0])
	last_best_color := 0
	last_best_cost := 0
	last_second_cost := 0
	for c := 0; c < k; c++ {
		cost := costs[n-1][c]
		if c == 0 {
			last_best_color = 0
			last_best_cost = costs[n-1][0]
		} else if c == 1 {
			last_second_cost = costs[n-1][1]
			if last_second_cost < last_best_cost {
				temp := last_best_cost
				last_best_cost = last_second_cost
				last_second_cost = temp
				last_best_color = 1
			}
		} else {
			if cost < last_best_cost {
				last_second_cost = last_best_cost
				last_best_cost = cost
				last_best_color = c
			} else if cost < last_second_cost {
				last_second_cost = cost
			}
		}
	}
	for i := n - 2; i >= 0; i-- {
		best_color := 0
		best_cost := 0
		second_cost := 0
		for c := 0; c < k; c++ {
			cost := costs[i][c]
			if c == last_best_color {
				cost = cost + last_second_cost
			} else {
				cost = cost + last_best_cost
			}
			if c == 0 {
				best_cost = cost
				best_color = 0
			} else if c == 1 {
				second_cost = cost
				if second_cost < best_cost {
					temp := best_cost
					best_cost = second_cost
					second_cost = temp
					best_color = 1
				}
			} else {
				if cost < best_cost {
					second_cost = best_cost
					best_cost = cost
					best_color = c
				} else if cost < second_cost {
					second_cost = cost
				}
			}
		}
		last_best_color = best_color
		last_best_cost = best_cost
		last_second_cost = second_cost
	}
	return last_best_cost
}

func Main() {
	answer := minCostII([][]int{[]int{1, 5, 3}, []int{2, 9, 4}})
	fmt.Println(answer)
}
