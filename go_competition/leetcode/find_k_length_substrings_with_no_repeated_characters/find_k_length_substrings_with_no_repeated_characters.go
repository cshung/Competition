package find_k_length_substrings_with_no_repeated_characters

import (
	"fmt"
)

func numKLenSubstrNoRepeats(s string, k int) int {
	n := len(s)
	if k > n {
		return 0
	}
	counts := make([]int, 256)
	repeated_letters := 0
	for i := 0; i < k; i++ {
		if counts[s[i]] > 0 {
			repeated_letters++
		}
		counts[s[i]]++
	}
	answer := 0
	if repeated_letters == 0 {
		answer = 1
	}
	for i := 1; i+k <= n; i++ {
		counts[s[i-1]]--
		if counts[s[i-1]] > 0 {
			repeated_letters--
		}
		if counts[s[i+k-1]] > 0 {
			repeated_letters++
		}
		counts[s[i+k-1]]++
		if repeated_letters == 0 {
			answer++
		}
	}
	return answer
}

func Main() {
	fmt.Println(numKLenSubstrNoRepeats("havefunonleetcode", 5))
}
