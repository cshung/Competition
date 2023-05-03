package find_the_difference_of_two_arrays

import (
	"fmt"
)

func findDifference(nums1 []int, nums2 []int) [][]int {
	s1a := map[int]struct{}{}
	s1b := map[int]struct{}{}
	s2a := map[int]struct{}{}
	s2b := map[int]struct{}{}
	for i := 0; i < len(nums1); i++ {
		s1a[nums1[i]] = struct{}{}
		s1b[nums1[i]] = struct{}{}
	}
	for i := 0; i < len(nums2); i++ {
		s2a[nums2[i]] = struct{}{}
		s2b[nums2[i]] = struct{}{}
	}
	for r, _ := range s2b {
		delete(s1a, r)
	}
	for r, _ := range s1b {
		delete(s2a, r)
	}
	left := []int{}
	right := []int{}

	for r, _ := range s1a {
		left = append(left, r)
	}
	for r, _ := range s2a {
		right = append(right, r)
	}
	return [][]int{left, right}
}

func Main() {
	answers := findDifference([]int{1, 2, 3}, []int{2, 4, 6})
	for i := 0; i < len(answers[0]); i++ {
		if i > 0 {
			fmt.Print(",")
		}
		fmt.Print(answers[0][i])
	}
	fmt.Println()
	for i := 0; i < len(answers[1]); i++ {
		if i > 0 {
			fmt.Print(",")
		}
		fmt.Print(answers[1][i])
	}
	fmt.Println()
}
