package perform_string_shifts

import (
	"fmt"
	"strings"
)

func stringShift(s string, shift [][]int) string {
	n := len(s)
	builder := strings.Builder{}
	offset := 0
	for i := 0; i < len(shift); i++ {
		offset = offset - (shift[i][0]*2-1)*shift[i][1]
		for offset < 0 {
			offset = (offset + n) % n
		}
	}
	for i := 0; i < n; i++ {
		builder.WriteByte(s[(i+offset)%n])
	}
	return builder.String()
}

func Main() {
	answer := stringShift("abc", [][]int{[]int{0, 1}, []int{1, 2}})
	fmt.Println(answer)
}
