package solving_questions_with_brainpower

import (
	"fmt"
)

func max(a, b int64) int64 {
	if a < b {
		return b
	}
	return a
}

func mostPoints(questions [][]int) int64 {
	n := len(questions)
	answers := make([]int64, n)
	for i := n - 1; i >= 0; i-- {
		skipped_index := i + questions[i][1] + 1
		taking_answer := int64(questions[i][0])
		skipping_answer := int64(0)
		if skipped_index < n {
			taking_answer = taking_answer + answers[skipped_index]
		}
		if i+1 < n {
			skipping_answer = skipping_answer + answers[i+1]
		}
		answers[i] = max(taking_answer, skipping_answer)
	}
	return answers[0]
}

func Main() {
	answer := mostPoints([][]int{[]int{3, 2}, []int{4, 3}, []int{4, 4}, []int{2, 5}})
	fmt.Println(answer)
}
