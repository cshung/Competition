package longest_arithmetic_subsequence

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func longestArithSeqLength(nums []int) int {
	n := len(nums)
	indexes := make(map[int]int)
	counts := make([][]int, n)
	for i := 0; i < n; i++ {
		counts[i] = make([]int, 500+499)
	}
	answer := 1
	for i := n - 1; i >= 0; i-- {
		v := nums[i]
		for j := -499; j <= 499; j++ {
			target := v + j
			next_index, ok := indexes[target]
			if ok {
				counts[i][j+499] = counts[next_index][j+499] + 1
				answer = max(answer, counts[i][j+499])
			}
		}
		indexes[v] = i
	}
	return answer + 1
}

func Main() {
	answer := longestArithSeqLength([]int{3, 6, 9, 12})
	fmt.Println(answer)
}
