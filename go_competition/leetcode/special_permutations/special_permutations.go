package special_permutations

import (
	"fmt"
)

func connected(nums []int, i int, j int) bool {
	ni := nums[i]
	nj := nums[j]
	return ((ni % nj) == 0) || ((nj % ni) == 0)
}

func specialPermHelper(nums []int, lastSelectedIndex int, selectedCount int, remainingMask int, memo [][]int) int {
	n := len(nums)
	if selectedCount == n {
		return 1
	}
	answer := 0
	b := 1
	for i := 0; i < n; i++ {
		if (b & remainingMask) != 0 {
			if selectedCount == 0 || connected(nums, lastSelectedIndex, i) {
				subProblemAnswer := 0
				if memo[i][remainingMask] != 0 {
					subProblemAnswer = memo[i][remainingMask] - 1
				} else {
					subProblemAnswer = specialPermHelper(nums, i, selectedCount+1, remainingMask-b, memo)
					memo[i][remainingMask] = subProblemAnswer + 1
				}
				answer += subProblemAnswer
				answer = answer % 1000000007
			}
		}
		b = b << 1
	}
	return answer
}

func specialPerm(nums []int) int {
	n := len(nums)
	s := 1 << n
	memo := make([][]int, n)
	for i := 0; i < n; i++ {
		memo[i] = make([]int, s)
	}
	return specialPermHelper(nums, -1, 0, s-1, memo)
}

func Main() {
	answer := specialPerm([]int{2, 3, 6})
	fmt.Println(answer)
}
