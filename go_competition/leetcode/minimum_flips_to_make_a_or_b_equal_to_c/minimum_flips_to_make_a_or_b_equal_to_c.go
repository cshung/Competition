package minimum_flips_to_make_a_or_b_equal_to_c

import (
	"fmt"
	"math/bits"
)

func minFlips(a int, b int, c int) int {
	a_or_b := a | b
	error := a_or_b ^ c
	error_0_1 := error & c
	error_x_0 := error & ^c
	error_2_0 := a & b & error_x_0
	error_1_0 := error_x_0 - error_2_0
	return bits.OnesCount(uint(error_1_0)) + 2*bits.OnesCount(uint(error_2_0)) + bits.OnesCount(uint(error_0_1))
}

func Main() {
	answer := minFlips(2, 6, 5)
	fmt.Println(answer)
}
