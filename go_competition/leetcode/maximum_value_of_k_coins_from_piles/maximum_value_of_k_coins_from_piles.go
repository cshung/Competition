package maximum_value_of_k_coins_from_piles

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func maxValueOfCoins(piles [][]int, k int) int {
	n := min(k, len(piles[0]))
	last_answers := []int{}
	sum := 0
	for i := 0; i < n; i++ {
		sum = sum + piles[0][i]
		last_answers = append(last_answers, sum)
	}
	count := len(piles[0])
	answers := []int{}

	for p := 1; p < len(piles); p++ {
		count = count + len(piles[p])
		n := min(count, k)
		for len(answers) < n {
			answers = append(answers, 0)
		}
		for i := 0; i < len(last_answers); i++ {
			answers[i] = last_answers[i]
		}
		for i := len(last_answers); i < n; i++ {
			answers[i] = 0
		}
		my_sum := 0
		for i := 0; i < min(len(piles[p]), k); i++ {
			my_sum = my_sum + piles[p][i]
			answers[i] = max(answers[i], my_sum)
			for j := 0; i+1+j < k && j < len(last_answers); j++ {
				answers[i+j+1] = max(answers[i+j+1], my_sum+last_answers[j])
			}
		}
		temp := last_answers
		last_answers = answers
		answers = temp
	}
	return last_answers[k-1]
}

func Main() {
	answer := maxValueOfCoins([][]int{[]int{1, 100, 3}, []int{7, 8, 9}}, 2)
	fmt.Println(answer)
}
