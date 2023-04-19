package longest_zigzag_path_in_a_binary_tree

import (
	"fmt"
)

// Definition for a binary tree node.
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type Summary struct {
	LeftLength  int
	RightLength int
}

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func longestZigZagHelper(root *TreeNode, answer *int) Summary {
	result := Summary{0, 0}
	if root.Left != nil {
		leftSummary := longestZigZagHelper(root.Left, answer)
		result.LeftLength = 1 + leftSummary.RightLength
		*answer = max(*answer, result.LeftLength)
	}
	if root.Right != nil {
		rightSummary := longestZigZagHelper(root.Right, answer)
		result.RightLength = 1 + rightSummary.LeftLength
		*answer = max(*answer, result.RightLength)
	}
	return result
}

func longestZigZag(root *TreeNode) int {
	answer := 0
	if root != nil {
		longestZigZagHelper(root, &answer)
	}
	return answer
}

func Main() {
	a := TreeNode{1, nil, nil}
	b := TreeNode{1, nil, nil}
	c := TreeNode{1, nil, nil}
	d := TreeNode{1, nil, nil}
	e := TreeNode{1, nil, nil}
	f := TreeNode{1, nil, nil}
	g := TreeNode{1, nil, nil}
	h := TreeNode{1, nil, nil}
	a.Right = &b
	b.Left = &c
	b.Right = &d
	d.Left = &e
	d.Right = &f
	e.Right = &g
	g.Right = &h
	answer := longestZigZag(&a)
	fmt.Println(answer)
}
