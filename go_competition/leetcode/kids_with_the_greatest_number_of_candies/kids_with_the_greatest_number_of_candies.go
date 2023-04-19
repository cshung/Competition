package kids_with_the_greatest_number_of_candies

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func kidsWithCandies(candies []int, extraCandies int) []bool {
	m := 0
	for i := 0; i < len(candies); i++ {
		m = max(m, candies[i])
	}
	answer := []bool{}
	for i := 0; i < len(candies); i++ {
		answer = append(answer, candies[i]+extraCandies >= m)
	}
	return answer
}

func Main() {
	answer := kidsWithCandies([]int{2, 3, 5, 1, 3}, 3)
	for i := 0; i < len(answer); i++ {
		fmt.Print(answer[i])
		fmt.Print(",")
	}
	fmt.Println()
}
