package k_radius_subarray_averages

import (
	"fmt"
)

func getAverages(nums []int, k int) []int {
	n := len(nums)
	answers := make([]int, n)
	s := 0
	w := 2*k + 1
	for i := 0; i <= k && i < n; i++ {
		s = s + nums[i]
	}
	for i := 0; i < n; i++ {
		if i-k < 0 || i+k >= n {
			answers[i] = -1
		} else {
			answers[i] = s / w
		}
		if i-k >= 0 {
			s -= nums[i-k]
		}
		if i+k+1 < n {
			s += nums[i+k+1]
		}
	}
	return answers
}

func Main() {
	answer := getAverages([]int{7, 4, 3, 9, 1, 8, 5, 2, 6}, 3)
	fmt.Println(answer)
}
