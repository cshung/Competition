package add_digits

import (
	"fmt"
)

func addDigits(num int) int {
	if num == 0 {
		return 0
	} else {
		return 1 + (num-1)%9
	}
}

func Main() {
	answer := addDigits(38)
	fmt.Println(answer)
}
