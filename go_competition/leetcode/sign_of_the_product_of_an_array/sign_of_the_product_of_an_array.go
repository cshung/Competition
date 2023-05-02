package sign_of_the_product_of_an_array

import (
	"fmt"
)

func arraySign(nums []int) int {
	answer := 1
	for i := 0; i < len(nums); i++ {
		n := nums[i]
		if n == 0 {
			return 0
		} else if n < 0 {
			answer = -answer
		}
	}
	return answer
}

func Main() {
	answer := arraySign([]int{-1, -2, -3, -4, 3, 2, 1})
	fmt.Println(answer)
}
