package minimum_operations_to_make_the_integer_zero

import (
	"fmt"
	"math/bits"
)

func makeTheIntegerZero(num1 int, num2 int) int {
	c := 0
	n1 := int64(num1)
	n2 := int64(num2)
	for {
		if n1 <= 0 {
			return -1
		}
		if c >= bits.OnesCount64(uint64(n1)) && n1 >= int64(c) {
			return c
		}
		c = c + 1
		n1 = n1 - n2
	}
}

func Main() {
	answer := makeTheIntegerZero(3, -2)
	fmt.Println(answer)
}
