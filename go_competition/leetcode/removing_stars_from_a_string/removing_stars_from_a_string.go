package removing_stars_from_a_string

import (
	"fmt"
	"strings"
)

func removeStars(s string) string {
	var stack []rune
	builder := strings.Builder{}
	for _, char := range s {
		if char == '*' {
			stack = stack[:len(stack)-1]
		} else {
			stack = append(stack, char)
		}
	}
	for i := 0; i < len(stack); i++ {
		builder.WriteString(string(stack[i]))
	}
	return builder.String()
}

func Main() {
	fmt.Println(removeStars("leet**cod*e"))
}
