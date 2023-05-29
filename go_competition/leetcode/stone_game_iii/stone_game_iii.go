package stone_game_iii

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func stoneGameIII(stoneValue []int) string {
	n := len(stoneValue)
	stoneValue = append(stoneValue, 0)
	stoneValue = append(stoneValue, 0)
	stoneValue = append(stoneValue, 0)
	running_sum := []int{0}
	sum := 0
	for i := 0; i < len(stoneValue); i++ {
		sum = sum + stoneValue[i]
		running_sum = append(running_sum, sum)
	}
	answers := make([]int, n+3)
	for i := n - 1; i >= 0; i-- {
		score := stoneValue[i] + ((running_sum[n] - running_sum[i+1]) - answers[i+1])
		score = max(score, (stoneValue[i]+stoneValue[i+1])+((running_sum[n]-running_sum[i+2])-answers[i+2]))
		score = max(score, (stoneValue[i]+stoneValue[i+1]+stoneValue[i+2])+((running_sum[n]-running_sum[i+3])-answers[i+3]))
		answers[i] = score
	}
	alice := answers[0]
	bob := sum - alice
	if alice > bob {
		return "Alice"
	} else if alice == bob {
		return "Tie"
	} else {
		return "Bob"
	}
}

func Main() {
	answer := stoneGameIII([]int{1, 2, 3, 7})
	fmt.Println(answer)
}
