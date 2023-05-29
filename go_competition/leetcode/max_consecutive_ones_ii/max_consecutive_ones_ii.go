package max_consecutive_ones_ii

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func findMaxConsecutiveOnes(nums []int) int {
	p := -1
	c := 0
	n := len(nums)
	answer := 0
	for i := 0; i < n; i++ {
		v := nums[i]
		if v == 0 {
			p = c
			c = 0
		} else {
			c = c + 1
		}
		answer = max(answer, p+1+c)
	}
	return answer
}

func Main() {
	answer := findMaxConsecutiveOnes([]int{1, 0, 1, 1, 0})
	fmt.Println(answer)
}
