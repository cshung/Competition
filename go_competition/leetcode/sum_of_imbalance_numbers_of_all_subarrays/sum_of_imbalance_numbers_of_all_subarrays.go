package sum_of_imbalance_numbers_of_all_subarrays

import (
	"fmt"
)

func sumImbalanceNumbers(nums []int) int {
	n := len(nums)
	count := 0
	for i := 0; i < n; i++ {

		v := nums[i]
		leftBound := 0
		leftOffender := -1
		for j := i - 1; j >= 0; j-- {
			if nums[j] == v+1 {
				leftBound = j + 1
				break
			} else if leftOffender == -1 && nums[j] > v+1 {
				leftOffender = j
			}
		}
		rightBound := n - 1
		rightOffender := -1
		for j := i + 1; j < n; j++ {
			if nums[j] == v+1 || nums[j] == v {
				rightBound = j - 1
				break
			} else if rightOffender == -1 && nums[j] > v+1 {
				rightOffender = j
			}
		}

		if leftOffender != -1 {
			leftCount := (leftOffender - leftBound + 1) * (rightBound - i + 1)
			count += leftCount
		}
		if rightOffender != -1 {
			rightCount := (rightBound - rightOffender + 1) * (i - leftBound + 1)
			count += rightCount
		}
		if leftOffender != -1 && rightOffender != -1 {
			bothCount := (rightBound - rightOffender + 1) * (leftOffender - leftBound + 1)
			count -= bothCount
		}
	}
	return count
}

func Main() {
	answer := sumImbalanceNumbers([]int{2, 3, 1, 4})
	fmt.Println(answer)
}
