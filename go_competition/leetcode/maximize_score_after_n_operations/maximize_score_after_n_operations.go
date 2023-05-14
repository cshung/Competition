package maximize_score_after_n_operations

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func gcd(a, b int) int {
	var _a, _b int = a, b
	for _b != 0 {
		tmp := _a
		_a = _b
		_b = tmp % _b
	}
	return _a
}

func maxScoreHelper(nums []int, n int, mask int, memo []int) int {
	if n == 0 {
		return 0
	}
	if memo[mask] != 0 {
		return memo[mask]
	}
	answer := 0
	for x := 0; x < len(nums); x++ {
		mask_x := 1 << x
		if (mask_x & mask) == 0 {
			for y := x + 1; y < len(nums); y++ {
				mask_y := 1 << y
				if (mask_y & mask) == 0 {
					answer = max(answer, n*gcd(nums[x], nums[y])+maxScoreHelper(nums, n-1, mask|mask_x|mask_y, memo))
				}
			}
		}
	}
	memo[mask] = answer
	return answer
}

func maxScore(nums []int) int {
	memo := make([]int, 16384)
	return maxScoreHelper(nums, len(nums)/2, 0, memo)
}

func Main() {
	// answer := maxScore([]int{1, 2})
	// answer := maxScore([]int{3, 4, 6, 8})
	answer := maxScore([]int{1, 2, 3, 4, 5, 6})
	fmt.Println(answer)
}
