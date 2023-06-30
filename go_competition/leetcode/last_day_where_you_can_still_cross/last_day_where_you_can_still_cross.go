package last_day_where_you_can_still_cross

import (
	"fmt"
)

func find(sets []int, i int) int {
	if sets[i] < 0 {
		return i
	} else {
		sets[i] = find(sets, sets[i])
		return sets[i]
	}
}

func union(sets []int, s1 int, s2 int) {
	i := find(sets, s1)
	j := find(sets, s2)
	if i != j {
		neg_size_i := sets[i]
		neg_size_j := sets[j]
		if neg_size_i > neg_size_j {
			sets[i] = j
			sets[j] = neg_size_i + neg_size_j
		} else {
			sets[j] = i
			sets[i] = neg_size_i + neg_size_j
		}
	}
}

func latestDayToCross(row int, col int, cells [][]int) int {
	n := row * col
	matrix := make([][]int, row)
	for r := 0; r < row; r++ {
		matrix[r] = make([]int, col)
	}

	drs := []int{1, -1, 0, 0}
	dcs := []int{0, 0, 1, -1}
	top := n
	bottom := n + 1
	sets := make([]int, n+2)
	for i := 0; i < n+2; i++ {
		sets[i] = -1
	}
	for i := n - 1; i >= 0; i-- {
		cell := cells[i]
		r := cell[0] - 1
		c := cell[1] - 1
		matrix[r][c] = 1
		s := r*col + c
		for d := 0; d < 4; d++ {
			nr := r + drs[d]
			nc := c + dcs[d]
			if 0 <= nr && nr < row && 0 <= nc && nc < col && matrix[nr][nc] == 1 {
				ns := nr*col + nc
				union(sets, s, ns)
			} else if nr == -1 {
				union(sets, s, top)
			} else if nr == row {
				union(sets, s, bottom)
			}
		}

		if find(sets, top) == find(sets, bottom) {
			return i
		}
	}

	return 10086
}

func Main() {
	answer := latestDayToCross(2, 2, [][]int{[]int{1, 1}, []int{2, 1}, []int{1, 2}, []int{2, 2}})
	fmt.Println(answer)
}
