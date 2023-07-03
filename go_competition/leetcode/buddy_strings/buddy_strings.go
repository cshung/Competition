package buddy_strings

import (
	"fmt"
)

func buddyStrings(s string, goal string) bool {
	n := len(s)
	if len(goal) != n {
		return false
	}
	seen := make([]bool, 26)
	a := "a"[0]
	dup := false
	mis := 0
	ms := "A"[0]
	mg := "A"[0]
	for i := 0; i < n; i++ {
		sc := s[i] - a
		gc := goal[i] - a
		if sc == gc {
			if seen[sc] {
				dup = true
			}
			seen[sc] = true
		} else if mis == 2 {
			return false
		} else if mis == 1 {
			if sc == mg && gc == ms {
				mis = 2
			} else {
				return false
			}
		} else if mis == 0 {
			ms = sc
			mg = gc
			mis = 1
		}
	}
	return mis == 2 || (mis == 0 && dup)
}

func Main() {
	answer := buddyStrings("ab", "ba")
	fmt.Println(answer)
}
