package profitable_schemes

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func profitableSchemes(n int, minProfit int, group []int, profit []int) int {
	lastAnswer := [][]int{}
	answer := [][]int{}
	for budget := 0; budget <= n; budget++ {
		lastAnswer = append(lastAnswer, []int{})
		answer = append(answer, []int{})
		for requiredProfit := 0; requiredProfit <= minProfit; requiredProfit++ {
			lastAnswer[budget] = append(lastAnswer[budget], 0)
			answer[budget] = append(answer[budget], 0)
		}
	}
	for budget := 0; budget <= n; budget++ {
		for requiredProfit := 0; requiredProfit <= minProfit; requiredProfit++ {
			lastAnswer[budget][requiredProfit] = 0
			if budget >= group[0] && profit[0] >= requiredProfit {
				lastAnswer[budget][requiredProfit] += 1
			}
			if requiredProfit == 0 {
				lastAnswer[budget][requiredProfit] += 1
			}
		}
	}

	for i := 1; i < len(group); i++ {
		for budget := 0; budget <= n; budget++ {
			for requiredProfit := 0; requiredProfit <= minProfit; requiredProfit++ {
				answer[budget][requiredProfit] = 0
				if budget >= group[i] {
					answer[budget][requiredProfit] += lastAnswer[budget-group[i]][max(requiredProfit-profit[i], 0)]
					answer[budget][requiredProfit] %= 1000000007
				}
				answer[budget][requiredProfit] += lastAnswer[budget][requiredProfit]
				answer[budget][requiredProfit] %= 1000000007
			}
		}
		temp := lastAnswer
		lastAnswer = answer
		answer = temp
	}

	return lastAnswer[n][minProfit]
}

func Main() {
	answer := profitableSchemes(5, 3, []int{2, 2}, []int{2, 3})
	fmt.Println(answer)
}
