package number_of_ways_to_reorder_array_to_get_same_bst

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type Ans struct {
	Length      int
	Numerator   int
	Denominator int
}

func solve(node *TreeNode) Ans {
	if node == nil {
		return Ans{0, 1, 1}
	} else {
		lAns := solve(node.Left)
		rAns := solve(node.Right)
		length := lAns.Length + rAns.Length + 1
		numerator := lAns.Numerator * rAns.Numerator % 1000000007
		denominator := (lAns.Denominator * rAns.Denominator % 1000000007) * length % 1000000007
		return Ans{length, numerator, denominator}
	}
}

func numOfWays(nums []int) int {
	n := len(nums)
	root := TreeNode{}
	for i := 0; i < n; i++ {
		num := nums[i]
		if i == 0 {
			root.Val = num
		} else {
			cur := &root
			for {
				if num < cur.Val {
					if cur.Left == nil {
						cur.Left = &TreeNode{}
						cur.Left.Val = num
						break
					} else {
						cur = cur.Left
					}
				} else {
					if cur.Right == nil {
						cur.Right = &TreeNode{}
						cur.Right.Val = num
						break
					} else {
						cur = cur.Right
					}
				}
			}
		}
	}
	ans := solve(&root)
	sol := ans.Numerator
	for i := 0; i < n; i++ {
		sol = sol * (i + 1) % 1000000007
	}
	sol = sol * modInverse(ans.Denominator, 1000000007) % 1000000007
	return (sol + 1000000007 - 1) % 1000000007
}

func modInverse(A int, M int) int {
	m0 := M
	y := 0
	x := 1

	if M == 1 {
		return 0
	}

	for A > 1 {
		// q is quotient
		q := A / M
		t := M

		// m is remainder now, process same as
		// Euclid's algo
		M = A % M
		A = t
		t = y

		// Update y and x
		y = x - q*y
		x = t
	}

	// Make x positive
	if x < 0 {
		x += m0
	}

	return x
}

func Main() {
	answer := numOfWays([]int{2, 1, 3})
	fmt.Println(answer)
}
