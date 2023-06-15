package maximum_level_sum_of_a_binary_tree

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func maxLevelSumHelper(node *TreeNode, level int, levelSums map[int]int) {
	if node != nil {
		levelSum, ok := levelSums[level]
		if !ok {
			levelSum = 0
		}
		levelSums[level] = levelSum + node.Val
		maxLevelSumHelper(node.Left, level+1, levelSums)
		maxLevelSumHelper(node.Right, level+1, levelSums)
	}
}

func maxLevelSum(root *TreeNode) int {
	levelSum := make(map[int]int)
	maxLevelSumHelper(root, 1, levelSum)
	found := false
	bestLevel := 0
	bestValue := 0
	for key, element := range levelSum {
		if !found {
			found = true
			bestLevel = key
			bestValue = element
		} else {
			if element > bestValue {
				bestValue = element
				bestLevel = key
			}
		}
	}
	return bestLevel
}

func Main() {
	a := TreeNode{7, nil, nil}
	b := TreeNode{7, nil, nil}
	c := TreeNode{-8, nil, nil}
	d := TreeNode{1, nil, nil}
	e := TreeNode{0, nil, nil}
	b.Left = &a
	b.Right = &c
	d.Left = &b
	d.Right = &e
	answer := maxLevelSum(&d)
	fmt.Println(answer)
}
