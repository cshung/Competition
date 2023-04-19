package number_of_ways_to_form_a_target_string_given_a_dictionary

import (
	"fmt"
)

func numWays(words []string, target string) int {
	l := len(target)
	m := len(words)
	n := len(words[0])
	a := "a"[0]
	counts := [][]int{}
	for i := 0; i < n; i++ {
		counts = append(counts, []int{})
		for j := 0; j < 26; j++ {
			counts[i] = append(counts[i], 0)
		}
		for k := 0; k < m; k++ {
			c := words[k][i] - a
			counts[i][c]++
		}
	}

	answer := []int{}
	last_answer := []int{}
	for i := 0; i <= n; i++ {
		answer = append(answer, 0)
		last_answer = append(last_answer, 1)
	}
	for t := l - 1; t >= 0; t-- {
		target_character := target[t] - a
		first := t
		last := n - ((l - 1) - t)
		answer[last] = 0
		for c := last - 1; c >= first; c-- {
			answer[c] = answer[c+1]
			answer[c] += counts[c][target_character] * last_answer[c+1]
			answer[c] = answer[c] % 1000000007
		}
		temp := last_answer
		last_answer = answer
		answer = temp
	}
	return last_answer[0]
}

func Main() {
	answer := numWays([]string{"acca", "bbbb", "caca"}, "aba")
	fmt.Println(answer)
}
