package longest_even_odd_subarray_with_threshold

import (
	"fmt"
)

func longestAlternatingSubarray(nums []int, threshold int) int {
	n := len(nums)
	answer := 0
	l := 0
	e := 0
	for i := n - 1; i >= 0; i-- {
		v := nums[i]
		if v > threshold {
			l = 0
			e = 0
		} else if v%2 == 0 {
			e = 1 + l
			l = 0
		} else {
			l = e + 1
			e = 0
		}
		if e > answer {
			answer = e
		}
	}
	return answer
}

func Main() {
	answer := longestAlternatingSubarray([]int{3, 2, 5, 4}, 5)
	fmt.Println(answer)
}
