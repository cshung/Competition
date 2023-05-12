package uncrossed_lines

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func maxUncrossedLines(nums1 []int, nums2 []int) int {
	l1 := len(nums1) + 1
	l2 := len(nums2) + 1
	answers := make([][]int, l1)
	for i := 0; i < l1; i++ {
		answers[i] = make([]int, l2)
	}
	for i := 1; i < l1; i++ {
		for j := 1; j < l2; j++ {
			if nums1[i-1] == nums2[j-1] {
				answers[i][j] = 1 + answers[i-1][j-1]
			} else {
				answers[i][j] = max(answers[i-1][j], answers[i][j-1])
			}
		}
	}
	return answers[l1-1][l2-1]
}

func Main() {
	answer := maxUncrossedLines([]int{2, 5, 1, 2, 5}, []int{10, 5, 2, 1, 5, 2})
	fmt.Println(answer)
}
