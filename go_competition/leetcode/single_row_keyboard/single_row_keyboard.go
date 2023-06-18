package single_row_keyboard

import (
	"fmt"
)

func calculateTime(keyboard string, word string) int {
	a := "a"[0]
	location := [26]int{}
	for i := 0; i < 26; i++ {
		location[keyboard[i]-a] = i
	}
	p := 0
	answer := 0
	for i := 0; i < len(word); i++ {
		c := word[i] - a
		l := location[c]
		d := l - p
		if d < 0 {
			d = -d
		}
		answer += d
		p = l
	}
	return answer
}

func Main() {
	answer := calculateTime("abcdefghijklmnopqrstuvwxyz", "cba")
	fmt.Println(answer)
}
