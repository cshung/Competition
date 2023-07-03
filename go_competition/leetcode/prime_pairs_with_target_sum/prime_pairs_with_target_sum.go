package prime_pairs_with_target_sum

import (
	"fmt"
)

func findPrimePairs(n int) [][]int {
	primeList := []int{}
	primeMap := make(map[int]bool)
	isPrime := make([]bool, n+1)
	for i := 2; i <= n; i++ {
		isPrime[i] = true
	}
	for i := 2; i <= n; i++ {
		if isPrime[i] {
			primeMap[i] = true
			primeList = append(primeList, i)
			if i*i <= n {
				for j := i * i; j <= n; j += i {
					isPrime[j] = false
				}
			}
		}
	}
	answer := [][]int{}
	half := n / 2
	for i := 0; i < len(primeList); i++ {
		p := primeList[i]
		if p > half {
			break
		}
		diff := n - p
		_, ok := primeMap[diff]
		if ok {
			answer = append(answer, []int{p, diff})
		}
	}
	return answer
}

func Main() {
	answer := findPrimePairs(10)
	fmt.Println(answer)
}
