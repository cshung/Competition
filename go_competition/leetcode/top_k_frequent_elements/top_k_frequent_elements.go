package top_k_frequent_elements

import (
	"fmt"
)

func topKFrequent(nums []int, k int) []int {
	frequencies := map[int]int{}
	counts := []int{0}

	for i := 0; i < len(nums); i++ {
		num := nums[i]
		frequency, found := frequencies[num]
		if found {
			counts[frequency]--
			frequencies[num] = frequency + 1
		} else {
			frequencies[num] = 1
		}
		frequency++
		if len(counts) < frequency+1 {
			counts = append(counts, 0)
		}
		counts[frequency] = counts[frequency] + 1
	}
	cursors := []int{0}
	for i := 1; i < len(counts); i++ {
		cursors = append(cursors, cursors[i-1]+counts[i])
	}

	n := cursors[len(cursors)-1]
	distinct := make([]int, n)
	for v, f := range frequencies {
		i := cursors[f-1]
		cursors[f-1] = cursors[f-1] + 1
		distinct[n-1-i] = v
	}
	return distinct[0:k]
}

func Main() {
	answers := topKFrequent([]int{1, 1, 1, 2, 2, 3}, 2)
	for i := 0; i < len(answers); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(answers[i])
	}
	fmt.Println()
}
