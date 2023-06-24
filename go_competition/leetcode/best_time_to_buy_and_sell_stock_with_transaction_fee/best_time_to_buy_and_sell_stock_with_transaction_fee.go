package best_time_to_buy_and_sell_stock_with_transaction_fee

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func maxProfit(prices []int, fee int) int {
	n := len(prices)
	a := 0
	b := prices[n-1] - fee
	for i := n - 1; i >= 0; i-- {
		p := prices[i]
		na := max(b-p, a)
		nb := max(p-fee+a, b)
		a = na
		b = nb
	}
	return a
}

func Main() {
	answer := maxProfit([]int{1, 3, 2, 8, 4, 9}, 2)
	fmt.Println(answer)
}
