package count_ways_to_build_good_strings

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func countGoodStrings(low int, high int, zero int, one int) int {
	window := max(zero, one)
	ways := make([]int, window)
	ways[0] = 1
	for i := 1; i < window; i++ {
		if i%zero == 0 {
			ways[i] = ways[i] + 1
		}
		if i%one == 0 {
			ways[i] = ways[i] + 1
		}
	}
	slot := 0
	answer := 0
	for l := window; l <= high; l++ {
		ways[slot] = ways[(slot+window-zero)%window] + ways[(slot+window-one)%window]
		ways[slot] = ways[slot] % 1000000007
		if l >= low {
			answer = answer + ways[slot]
			answer = answer % 1000000007
		}
		slot = (slot + 1) % window
	}
	return answer
}

func Main() {
	answer := countGoodStrings(3, 3, 1, 1)
	fmt.Println(answer)
}
