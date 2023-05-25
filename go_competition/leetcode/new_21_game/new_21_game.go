package new_21_game

import (
	"fmt"
)

func new21Game(n int, k int, maxPts int) float64 {
	if k == 0 {
		return float64(1)
	}
	sum := float64(0)
	tail := 0
	head := 0
	prob := make([]float64, maxPts)
	i := 1
	answer := float64(0)
	for {
		if i == maxPts+k {
			break
		}
		p := sum / float64(maxPts)
		if i <= maxPts {
			p = p + float64(1)/float64(maxPts)
		} else {
			sum = sum - prob[head]
			head = head + 1
			if head == maxPts {
				head = 0
			}
		}
		if i < k {
			prob[tail] = p
			tail = tail + 1
			if tail == maxPts {
				tail = 0
			}
			sum = sum + p
		}
		if i > n {
			answer = answer + p
		}

		i = i + 1
	}
	return 1 - answer
}

func Main() {
	answer := new21Game(21, 17, 10)
	fmt.Println(answer)
}
