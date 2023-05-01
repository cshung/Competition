package average_salary_excluding_the_minimum_and_maximum_salary

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

func average(salary []int) float64 {
	min_salary := salary[0]
	max_salary := salary[0]
	sum := salary[0]
	for i := 1; i < len(salary); i++ {
		s := salary[i]
		min_salary = min(min_salary, s)
		max_salary = max(max_salary, s)
		sum = sum + s
	}
	return float64(sum-min_salary-max_salary) / float64(len(salary)-2)
}

func Main() {
	answer := average([]int{4000, 3000, 1000, 2000})
	fmt.Println(answer)
}
