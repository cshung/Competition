package shortest_way_to_form_string

import (
	"fmt"
)

func shortestWay(source string, target string) int {
	a := "a"[0]
	m := len(source)
	n := len(target)
	s := []byte(source)
	t := []byte(target)

	indices := make([][]int, 26)
	for i := 0; i < 26; i++ {
		indices[i] = []int{}
	}
	for i := 0; i < m; i++ {
		c := s[i] - a
		indices[c] = append(indices[c], i+1)
	}
	next := make([][]int, m+1)
	for i := 0; i < m+1; i++ {
		next[i] = make([]int, 26)
	}
	for i := 0; i < 26; i++ {
		k := 0
		for j := 0; j < m+1; j++ {
			z := m + 1
			if k < len(indices[i]) {
				z = indices[i][k]
			}
			next[j][i] = z
			if j+1 == z {
				k = k + 1
			}
		}
	}
	ti := 0
	si := 0
	answer := 0
	for {
		answer = answer + 1
		progress := false
		for {
			c := t[ti] - a
			si = next[si][c]
			if si == m+1 {
				si = 0
				break
			} else {
				progress = true
				ti = ti + 1
				if ti == n {
					break
				}
			}
		}
		if !progress {
			return -1
		}
		if ti == n {
			break
		}
	}
	return answer
}

func Main() {
	answer := shortestWay("abc", "abcbc")
	fmt.Println(answer)
}
