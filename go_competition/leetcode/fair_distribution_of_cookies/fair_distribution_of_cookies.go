package fair_distribution_of_cookies

import (
	"fmt"
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func distributeCookiesHelper(cookies []int, k int, chosen int, memo [][]int) int {
	if memo[chosen][k] != 0 {
		return memo[chosen][k] - 1
	}
	n := len(cookies)
	available := []int{}
	sum := 0
	for i := 0; i < n; i++ {
		mask := 1 << i
		if mask&chosen == 0 {
			available = append(available, i)
			sum = sum + cookies[i]
		}
	}
	if k == 1 {
		return sum
	}

	answer := 0
	a := len(available)
	p := 1 << a
	for i := 0; i < p; i++ {
		chosenNow := 0
		myShare := 0
		for s := 0; s < a; s++ {
			mask := 1 << s
			if mask&i != 0 {
				myShare = myShare + cookies[available[s]]
				chosenNow = chosenNow | 1<<available[s]
			}
		}
		subproblem := max(myShare, distributeCookiesHelper(cookies, k-1, chosen|chosenNow, memo))
		if answer == 0 {
			answer = subproblem
		} else {
			answer = min(answer, subproblem)
		}
	}

	memo[chosen][k] = answer + 1
	return answer

}

func distributeCookies(cookies []int, k int) int {
	n := len(cookies)
	p := 1 << n
	memo := make([][]int, p)
	for i := 0; i < p; i++ {
		memo[i] = make([]int, k+1)
	}
	return distributeCookiesHelper(cookies, k, 0, memo)
}

func Main() {
	answer := distributeCookies([]int{8, 15, 10, 20, 8}, 2)
	fmt.Println(answer)
}
