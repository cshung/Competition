package stone_game_ii

import (
	"fmt"
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

func max_m(r int) int {
	if r%2 == 1 {
		r = r + 1
	}
	return r / 2
}

func stoneGameII(piles []int) int {
	n := len(piles)
	answers := [][][]int{}
	for p := 0; p < 2; p++ {
		answers_for_player := [][]int{}
		for i := 0; i < n; i++ {
			r := n - i
			m_max := max_m(r)
			answers_for_player = append(answers_for_player, make([]int, m_max))
		}
		answers = append(answers, answers_for_player)
	}

	for i := n - 1; i >= 0; i-- {
		r := n - i
		m_max := max_m(r)
		for m := 1; m <= m_max; m++ {
			sum := 0
			max_score := 0
			min_score := 0
			for j := 1; j <= min(2*m, r); j++ {
				sum = sum + piles[i+j-1]
				new_r := r - j
				new_max_score := sum
				new_min_score := 0
				if new_r > 0 {
					new_m := min(max(m, j), max_m(new_r))
					new_max_score += answers[1][i+j][new_m-1]
					new_min_score += answers[0][i+j][new_m-1]
				}
				if j == 1 {
					max_score = new_max_score
					min_score = new_min_score
				} else {
					max_score = max(new_max_score, max_score)
					min_score = min(new_min_score, min_score)
				}
			}
			answers[0][i][m-1] = max_score
			answers[1][i][m-1] = min_score
		}
	}
	return answers[0][0][0]
}

func Main() {
	answer := stoneGameII([]int{2, 7, 9, 4, 4})
	fmt.Println(answer)
}
