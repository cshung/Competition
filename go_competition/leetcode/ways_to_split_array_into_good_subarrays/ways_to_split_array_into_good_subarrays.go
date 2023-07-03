package ways_to_split_array_into_good_subarrays

import (
	"fmt"
)

func numberOfGoodSubarraySplits(nums []int) int {
	n := len(nums)
	s := 1
	a := 0
	for i := n - 1; i >= 0; i-- {
		v := nums[i]
		if v == 0 {
			s = s + a
			s = s % 1000000007
		} else {
			a = s + a
			a = a % 1000000007
			s = 0
		}
	}
	return a
}

func Main() {
	answer := numberOfGoodSubarraySplits([]int{0, 1, 0, 0, 1})
	fmt.Println(answer)
}
