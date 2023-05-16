package confusing_number

import (
	"fmt"
)

func confusingNumber(n int) bool {
	rev := 0
	org := n
	for n > 0 {
		d := n % 10
		if d == 2 || d == 3 || d == 4 || d == 5 || d == 7 {
			return false
		} else if d == 6 || d == 9 {
			d = 15 - d
		}
		rev = rev*10 + d
		n = n / 10
	}
	return rev != org
}

func Main() {
	answer := confusingNumber(6)
	fmt.Println(answer)
}
