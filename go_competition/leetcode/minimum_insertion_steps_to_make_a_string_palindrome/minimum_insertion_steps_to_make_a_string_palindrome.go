package minimum_insertion_steps_to_make_a_string_palindrome

import (
	"fmt"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func minInsertions(s string) int {
	n := len(s)
	answer := [][]int{}
	for i := 0; i <= n; i++ {
		answer = append(answer, []int{})
		for j := 0; j <= n; j++ {
			answer[i] = append(answer[i], 0)
		}
	}
	for length := 2; length <= n; length++ {
		for start := 0; start+length <= n; start++ {
			answer[start][start+length] = 1 + min(answer[start+1][start+length], answer[start][start+length-1])
			if s[start] == s[start+length-1] {
				answer[start][start+length] = min(answer[start][start+length], answer[start+1][start+length-1])
			}
		}
	}
	return answer[0][n]
}

func Main() {
	answer := minInsertions("leetcode")
	fmt.Println(answer)
}
