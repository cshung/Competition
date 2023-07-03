package continuous_subarrays

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func continuousSubarrays(nums []int) int64 {
	n := len(nums)
	start := 0
	count := int64(1)
	windowMin := nums[0]
	windowMax := nums[0]
	pure_tail_value := nums[0]
	pure_tail_start := 0
	mixed_tail_value := -1
	mixed_tail_start := -1
	for i := 1; i < n; i++ {
		v := nums[i]
		if v < windowMin {
			if v < windowMax-2 {
				if mixed_tail_start != -1 && mixed_tail_value <= v+2 && pure_tail_value <= v+2 {
					start = mixed_tail_start
					windowMin = v
					windowMax = max(pure_tail_value, mixed_tail_value)
				} else if pure_tail_value <= v+2 {
					mixed_tail_start = -1
					start = pure_tail_start
					windowMax = pure_tail_value
					windowMin = v
					windowMax = pure_tail_value
				} else {
					start = i
					pure_tail_value = v
					pure_tail_start = i
					mixed_tail_value = -1
					mixed_tail_start = -1
					windowMin = v
					windowMax = v
				}
			} else {
				windowMin = v
			}
		} else if v > windowMax {
			if v > windowMin+2 {
				if mixed_tail_start != -1 && mixed_tail_value >= v-2 && pure_tail_value >= v-2 {
					start = mixed_tail_start
					windowMin = min(pure_tail_value, mixed_tail_value)
					windowMax = v
				} else if pure_tail_value >= v-2 {
					mixed_tail_start = -1
					start = pure_tail_start
					windowMin = pure_tail_value
					windowMax = v
				} else {
					start = i
					pure_tail_value = v
					pure_tail_start = i
					mixed_tail_value = -1
					mixed_tail_start = -1
					windowMin = v
					windowMax = v
				}
			} else {
				windowMax = v
			}
		}
		count = count + int64(i-start+1)
		if v != pure_tail_value {
			if v == mixed_tail_value {
				pure_tail_value, pure_tail_start, mixed_tail_value, mixed_tail_start = v, i, pure_tail_value, mixed_tail_start
			} else if (v == pure_tail_value+1) || v == (pure_tail_value-1) {
				pure_tail_value, pure_tail_start, mixed_tail_value, mixed_tail_start = v, i, pure_tail_value, pure_tail_start
			} else {
				pure_tail_value, pure_tail_start, mixed_tail_value, mixed_tail_start = v, i, -1, -1
			}
		}
	}
	return count
}

func Main() {
	answer := continuousSubarrays([]int{5, 4, 2, 4})
	fmt.Println(answer)
}
