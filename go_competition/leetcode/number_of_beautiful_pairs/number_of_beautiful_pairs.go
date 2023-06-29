package number_of_beautiful_pairs

import (
	"fmt"
)

func gcd(a, b int) int {
	var _a, _b int = a, b
	for _b != 0 {
		tmp := _a
		_a = _b
		_b = tmp % _b
	}
	return _a
}

func lsb(a int) int {
	return a % 10
}

func msb(a int) int {
	for a >= 10 {
		a = a / 10
	}
	return a
}

func countBeautifulPairs(nums []int) int {
	n := len(nums)
	m := make([]int, n)
	l := make([]int, n)
	answer := 0
	for i := 0; i < n; i++ {
		m[i] = msb(nums[i])
		l[i] = lsb(nums[i])
	}
	for i := 0; i < n; i++ {
		mi := m[i]
		for j := i + 1; j < n; j++ {
			lj := l[j]
			if gcd(mi, lj) == 1 {
				answer = answer + 1
			}
		}
	}
	return answer
}

func Main() {
	answer := countBeautifulPairs([]int{2, 5, 1, 4})
	fmt.Println(answer)
}
