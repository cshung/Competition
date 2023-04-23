package restore_the_array

import (
	"fmt"
)

func numberOfArrays(s string, k int) int {
	n := len(s)
	digits := []int{}
	zero := "0"[0]
	for i := 0; i < n; i++ {
		digits = append(digits, int(s[i]-zero))
	}
	answer := []int{}
	answer = append(answer, 1)
	if digits[0] == 0 {
		return 0
	} else if digits[0] > k {
		return 0
	}
	answer = append(answer, 1)
	for end := 1; end < n; end++ {
		base := 1
		num := 0
		count := 0
		for start := end; start >= 0; start-- {
			d := digits[start]
			num = num + d*base
			base = base * 10
			if num > k {
				break
			}
			if d != 0 {
				count = count + answer[start]
			}
		}
		answer = append(answer, count)
	}

	return answer[n]
}

func Main() {
	answer := numberOfArrays("1000", 10000)
	fmt.Println(answer)
}
