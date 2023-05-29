package longest_substring_with_at_most_two_distinct_characters

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func lengthOfLongestSubstringTwoDistinct(s string) int {
	sb := []byte(s)
	n := len(sb)
	ws := 0
	we := 1
	count := make([]int, 256)
	count[sb[0]] = 1
	distinct := 1
	largest := 1
	for ws < n {
		if we < n && (distinct < 2 || count[sb[we]] != 0) {
			if count[sb[we]] == 0 {
				distinct++
			}
			count[sb[we]]++
			we++
		} else {
			largest = max(largest, we-ws)
			count[sb[ws]]--
			if count[sb[ws]] == 0 {
				distinct--
			}
			ws++
		}
	}
	return largest
}

func Main() {
	answer := lengthOfLongestSubstringTwoDistinct("eceba")
	fmt.Println(answer)
}
