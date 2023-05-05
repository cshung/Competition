package maximum_number_of_vowels_in_a_substring_of_given_length

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func maxVowels(s string, k int) int {
	a := "a"[0]
	e := "e"[0]
	i := "i"[0]
	o := "o"[0]
	u := "u"[0]
	v := 0
	for t := 0; t < k; t++ {
		if s[t] == a || s[t] == e || s[t] == i || s[t] == o || s[t] == u {
			v = v + 1
		}
	}
	answer := v
	for t := k; t < len(s); t++ {
		if s[t] == a || s[t] == e || s[t] == i || s[t] == o || s[t] == u {
			v = v + 1
		}
		if s[t-k] == a || s[t-k] == e || s[t-k] == i || s[t-k] == o || s[t-k] == u {
			v = v - 1
		}
		answer = max(answer, v)
	}
	return answer
}

func Main() {
	fmt.Println(maxVowels("abciiidef", 3))
	fmt.Println(maxVowels("aeiou", 2))
	fmt.Println(maxVowels("leetcode", 3))
}
