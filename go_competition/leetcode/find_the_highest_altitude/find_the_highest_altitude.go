package find_the_highest_altitude

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func largestAltitude(gain []int) int {
	level := 0
	maxLevel := 0
	for i := 0; i < len(gain); i++ {
		level = level + gain[i]
		maxLevel = max(level, maxLevel)
	}
	return maxLevel
}

func Main() {
	answer := largestAltitude([]int{-5, 1, 5, 0, -7})
	fmt.Println(answer)
}
