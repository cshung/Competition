package find_the_value_of_the_partition

import (
	"fmt"
	"sort"
)

func findValueOfPartition(nums []int) int {
	sort.Ints(nums)
	minDiff := nums[1] - nums[0]
	for i := 2; i < len(nums); i++ {
		diff := nums[i] - nums[i-1]
		if diff < minDiff {
			minDiff = diff
		}
	}
	return minDiff
}

func Main() {
	answer := findValueOfPartition([]int{1, 3, 2, 4})
	fmt.Println(answer)
}
