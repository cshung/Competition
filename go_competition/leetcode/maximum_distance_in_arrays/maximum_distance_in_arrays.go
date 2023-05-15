package maximum_distance_in_arrays

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func maxDistance(arrays [][]int) int {
	first_max := 0
	first_max_index := 0
	second_max := 0
	first_min := 0
	first_min_index := 0
	second_min := 0
	for i := 0; i < len(arrays); i++ {
		array_min := arrays[i][0]
		array_max := arrays[i][len(arrays[i])-1]
		if i == 0 {
			first_min = array_min
			first_min_index = 0
			first_max = array_max
			first_max_index = 0
		} else if i == 1 {
			if array_min < first_min {
				second_min = first_min
				first_min = array_min
				first_min_index = 1
			} else {
				second_min = array_min
			}
			if array_max > first_max {
				second_max = first_max
				first_max = array_max
				first_max_index = 1
			} else {
				second_max = array_max
			}
		} else {
			if array_min < first_min {
				second_min = first_min
				first_min = array_min
				first_min_index = i
			} else if array_min < second_min {
				second_min = array_min
			}
			if array_max > first_max {
				second_max = first_max
				first_max = array_max
				first_max_index = i
			} else if array_max > second_max {
				second_max = array_max
			}
		}
	}
	if first_min_index == first_max_index {
		return max(second_max-first_min, first_max-second_min)
	} else {
		return first_max - first_min
	}
}

func Main() {
	answer := maxDistance([][]int{[]int{1, 2, 3}, []int{4, 5}, []int{1, 2, 3}})
	fmt.Println(answer)
}
