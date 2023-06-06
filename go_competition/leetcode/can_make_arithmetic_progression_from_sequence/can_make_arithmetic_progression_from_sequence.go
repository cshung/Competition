package can_make_arithmetic_progression_from_sequence

import (
	"fmt"
)

func canMakeArithmeticProgression(arr []int) bool {
	n := len(arr)
	min := arr[0]
	sec := arr[1]
	if arr[1] < min {
		min = arr[1]
		sec = arr[0]
	}
	for i := 2; i < n; i++ {
		c := arr[i]
		if c < min {
			sec = min
			min = c
		} else if c < sec {
			sec = c
		}
	}
	a := min
	d := sec - min
	if d == 0 {
		for i := 0; i < n; i++ {
			if arr[i] != a {
				return false
			}
		}
		return true
	} else {
		for i := 0; i < n; i++ {
			t := arr[i]
			t = t - a
			if t%d == 0 {
				t = t / d
				if t >= n {
					return false
				}
			} else {
				return false
			}
			arr[i] = t
		}
		for i := 0; i < n; i++ {
			s := i
			c := s
			if arr[c] != n {
				for {
					next := arr[c]
					arr[c] = n
					if next == s {
						break
					}
					if next == n {
						return false
					}
					c = next
				}
			}
		}
		return true
	}
}

func Main() {
	answer := canMakeArithmeticProgression([]int{3, 5, 1})
	fmt.Println(answer)
}
