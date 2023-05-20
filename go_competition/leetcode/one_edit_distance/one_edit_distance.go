package one_edit_distance

import (
	"fmt"
)

func isOneEditDistance(s string, t string) bool {
	s = s + "x"
	t = t + "x"
	si := 0
	ti := 0
	found := false
	for si < len(s) && ti < len(t) {
		if s[si] != t[ti] {
			if found {
				return false
			} else if len(s)-len(t) == 1 {
				ti = ti - 1
			} else if len(t)-len(s) == 1 {
				si = si - 1
			} else if len(s) != len(t) {
				return false
			}
			found = true
		}
		si = si + 1
		ti = ti + 1
	}
	return found
}

func Main() {
	answer := isOneEditDistance("ab", "acb")
	fmt.Println(answer)
}
