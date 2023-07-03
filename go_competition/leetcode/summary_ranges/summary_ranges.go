package summary_ranges

import (
	"fmt"
)

func summaryRanges(nums []int) []string {
	i := 0
	n := len(nums)
	answers := []string{}
	for i < n {
		j := i
		for (j < n) && ((j == i) || (nums[j] == nums[j-1]+1)) {
			j++
		}
		if i == (j - 1) {
			answers = append(answers, fmt.Sprintf("%d", nums[i]))

		} else {
			answers = append(answers, fmt.Sprintf("%d->%d", nums[i], nums[j-1]))
		}
		i = j
	}
	return answers
}

func Main() {
	answer := summaryRanges([]int{0, 1, 2, 4, 5, 7})
	fmt.Println(answer)
}
