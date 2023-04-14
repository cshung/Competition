package longest_palindromic_subsequence

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func longestPalindromeSubseq(s string) int {
	chars := []rune{}
	for _, char := range s {
		chars = append(chars, char)
	}
	n := len(s)
	a := 'a'
	index := [][]int{}
	for i := 0; i < 26; i++ {
		index = append(index, []int{})
		cur := -1
		for j := 0; j < len(chars); j++ {
			if chars[j] == a+rune(i) {
				cur = j
			}
			index[i] = append(index[i], cur)
		}
	}
	answer := [][]int{}
	for i := 0; i <= n; i++ {
		answer = append(answer, []int{})
		for j := 0; j <= n; j++ {
			answer[i] = append(answer[i], 0)
		}
	}
	for length := 1; length <= n; length++ {
		for start_index := 0; start_index+length <= n; start_index++ {
			end_index := start_index + length
			start_character := chars[start_index]
			match_index := index[start_character-a][end_index-1]

			case1 := 0
			if match_index == start_index {
				case1 = 1
			} else {
				case1 = 2 + answer[start_index+1][match_index]
			}
			case2 := answer[start_index+1][end_index]
			answer[start_index][end_index] = max(case1, case2)
		}
	}
	return answer[0][n]
}

func Longest_palindromic_subsequence() {
	fmt.Println(longestPalindromeSubseq("bbbab"))
}
