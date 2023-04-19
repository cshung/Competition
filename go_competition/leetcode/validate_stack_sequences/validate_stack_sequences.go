package validate_stack_sequences

import (
	"fmt"
)

func validateStackSequences(pushed []int, popped []int) bool {
	push := 0
	pop := 0
	stack := []int{}
	for {
		if len(stack) > 0 && stack[len(stack)-1] == popped[pop] {
			stack = stack[:(len(stack) - 1)]
			pop = pop + 1
		} else if push < len(pushed) {
			stack = append(stack, pushed[push])
			push = push + 1
		} else if push == len(pushed) && pop == len(popped) {
			return true
		} else {
			return false
		}
	}
}

func Main() {
	fmt.Println(validateStackSequences([]int{1, 2, 3, 4, 5}, []int{4, 5, 3, 2, 1}))
}
