package find_anagram_mappings

import (
	"fmt"
)

func anagramMappings(nums1 []int, nums2 []int) []int {
	numToIndexesMap := make(map[int][]int)
	l := len(nums1)
	for i := 0; i < l; i++ {
		n := nums2[i]
		indexes, ok := numToIndexesMap[n]
		if !ok {
			indexes = []int{}
		}
		indexes = append(indexes, i)
		numToIndexesMap[n] = indexes
	}
	answers := make([]int, l)
	for i := 0; i < l; i++ {
		n := nums1[i]
		indexes := numToIndexesMap[n]
		answers[i] = indexes[len(indexes)-1]
		indexes = indexes[:len(indexes)-1]
		numToIndexesMap[n] = indexes
	}
	return answers
}

func Main() {
	answers := anagramMappings([]int{12, 28, 46, 32, 50}, []int{50, 12, 32, 46, 28})
	for i := 0; i < len(answers); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(answers[i])
	}
	fmt.Println()
}
