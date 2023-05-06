package number_of_subsequences_that_satisfy_the_given_sum_condition

import (
	"fmt"
	"sort"
)

func pow(n int) int {
	if n == 0 {
		return 1
	} else {
		half := pow(n / 2)
		ans := (half * half) % 1000000007
		if n%2 == 1 {
			ans = ans * 2 % 1000000007
		}
		return ans
	}
}

func numSubseq(nums []int, target int) int {
	sort.Ints(nums)
	answer := 0
	for i := 0; i < len(nums); i++ {
		index := sort.SearchInts(nums, target-nums[i]+1)
		if index > i {
			answer = answer + pow(index-i-1)
			answer = answer % 1000000007
		}
	}
	return answer
}

func Main() {
	answer := numSubseq([]int{3, 5, 6, 7}, 9)
	fmt.Println(answer)
}
