package find_the_longest_valid_obstacle_course_at_each_position

import (
	"fmt"
	"sort"
)

func longestObstacleCourseAtEachPosition(obstacles []int) []int {
	answers := []int{1}
	ends := []int{obstacles[0]}
	for i := 1; i < len(obstacles); i++ {
		index := sort.SearchInts(ends, obstacles[i]+1)
		answer := 0
		if index == 0 {
			ends[0] = obstacles[i]
			answer = 1
		} else if index == len(ends) {
			ends = append(ends, obstacles[i])
			answer = index + 1
		} else {
			ends[index] = obstacles[i]
			answer = index + 1
		}
		answers = append(answers, answer)
	}
	return answers
}

func Main() {
	answers := longestObstacleCourseAtEachPosition([]int{1, 2, 3, 2})
	for i := 0; i < len(answers); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(answers[i])
	}
	fmt.Println()
}
