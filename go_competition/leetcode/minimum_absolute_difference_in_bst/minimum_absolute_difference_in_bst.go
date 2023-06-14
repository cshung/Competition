package minimum_absolute_difference_in_bst

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
func inorder(root *TreeNode, state *int, last *int, answer *int) {
	if root != nil {
		inorder(root.Left, state, last, answer)
		if *state == 0 {
			*state = 1
		} else if *state == 1 {
			*state = 2
			*answer = root.Val - *last
		} else {
			*answer = min(root.Val-*last, *answer)
		}
		*last = root.Val
		inorder(root.Right, state, last, answer)
	}
}

func getMinimumDifference(root *TreeNode) int {
	state := 0
	last := 0
	answer := 0
	inorder(root, &state, &last, &answer)
	return answer
}

func Main() {
	a := TreeNode{1, nil, nil}
	b := TreeNode{2, nil, nil}
	c := TreeNode{3, nil, nil}
	d := TreeNode{4, nil, nil}
	e := TreeNode{6, nil, nil}
	b.Left = &a
	b.Right = &c
	d.Left = &b
	d.Right = &e
	answer := getMinimumDifference(&d)
	fmt.Println(answer)
}
