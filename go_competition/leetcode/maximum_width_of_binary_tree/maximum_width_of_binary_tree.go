package maximum_width_of_binary_tree

import (
	"fmt"
)

// Definition for a binary tree node.
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func widthOfBinaryTreeHelper(id int, height int, root *TreeNode, min *[]int, max *[]int, answer *int) {
	if len(*min) == height {
		*min = append(*min, id)
		*max = append(*max, id)
	} else {
		if id < (*min)[height] {
			(*min)[height] = id
		}
		if id > (*max)[height] {
			(*max)[height] = id
		}
		width := (*max)[height] - (*min)[height] + 1
		if *answer < width {
			*answer = width
		}
	}
	if root.Left != nil {
		widthOfBinaryTreeHelper(id*2, height+1, root.Left, min, max, answer)
	}
	if root.Right != nil {
		widthOfBinaryTreeHelper(id*2+1, height+1, root.Right, min, max, answer)
	}
}

func widthOfBinaryTree(root *TreeNode) int {
	min := []int{}
	max := []int{}
	answer := 1
	widthOfBinaryTreeHelper(0, 0, root, &min, &max, &answer)
	return answer
}

func Main() {
	a := TreeNode{1, nil, nil}
	b := TreeNode{3, nil, nil}
	c := TreeNode{2, nil, nil}
	d := TreeNode{5, nil, nil}
	e := TreeNode{3, nil, nil}
	f := TreeNode{9, nil, nil}
	a.Left = &b
	a.Right = &c
	b.Left = &d
	b.Right = &e
	c.Right = &f
	answer := widthOfBinaryTree(&a)
	fmt.Println(answer)
}
