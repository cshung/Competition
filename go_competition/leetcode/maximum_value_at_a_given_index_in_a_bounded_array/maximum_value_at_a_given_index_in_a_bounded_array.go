package maximum_value_at_a_given_index_in_a_bounded_array

import (
	"fmt"
	"math"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func sum(v int, l int) int {
	if v < l {
		return (v+1)*v/2 + (l - v)
	} else {
		return (2*v - l + 1) * l / 2
	}
}

func maxValue(n int, index int, maxSum int) int {
	leftLength := index + 1
	rightLength := n - index
	a := min(leftLength, rightLength)
	b := max(leftLength, rightLength)
	if (sum(a, a) + sum(a, b) - a) > maxSum {
		return int(math.Sqrt(float64(maxSum-a-b+1))) + 1
	} else if (sum(b, a) + sum(b, b) - a) > maxSum {
		return (int(math.Sqrt(float64(8*maxSum-(-8*a*a+16*a+8*b-9)))) + 3 - 2*a) / 2
	} else {
		return (a*a - a + b*b - b + 2*maxSum) / (2 * (a + b - 1))
	}
	return 0
}

func Main() {
	answer := maxValue(4, 2, 6)
	fmt.Println(answer)
}
