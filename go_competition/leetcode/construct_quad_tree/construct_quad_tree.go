package construct_quad_tree

import "fmt"

type Node struct {
	Val         bool
	IsLeaf      bool
	TopLeft     *Node
	TopRight    *Node
	BottomLeft  *Node
	BottomRight *Node
}

func construct_helper(sums [][]int, r1 int, c1 int, r2 int, c2 int) *Node {
	size := (r2 - r1) * (c2 - c1)
	sum := sums[r2][c2] - sums[r2][c1] - sums[r1][c2] + sums[r1][c1]
	if sum == 0 {
		return &Node{false, true, nil, nil, nil, nil}
	} else if sum == size {
		return &Node{true, true, nil, nil, nil, nil}
	} else {
		mid_r := (r1 + r2) / 2
		mid_c := (c1 + c2) / 2
		return &Node{
			false,
			false,
			construct_helper(sums, r1, c1, mid_r, mid_c),
			construct_helper(sums, r1, mid_c, mid_r, c2),
			construct_helper(sums, mid_r, c1, r2, mid_c),
			construct_helper(sums, mid_r, mid_c, r2, c2),
		}
	}
}

func construct(grid [][]int) *Node {
	n := len(grid)
	sums := make([][]int, n+1)
	for i := 0; i < n+1; i++ {
		sums[i] = make([]int, n+1)
	}
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			sums[i+1][j+1] = grid[i][j]
			sums[i+1][j+1] += sums[i][j+1]
			sums[i+1][j+1] += sums[i+1][j]
			sums[i+1][j+1] -= sums[i][j]
		}
	}
	return construct_helper(sums, 0, 0, n, n)
}

func displayQuadTree(root *Node, level int) {
	for i := 0; i < level; i++ {
		fmt.Printf(" ")
	}
	if root.IsLeaf {
		fmt.Println(root.Val)
	} else {
		displayQuadTree(root.TopLeft, level+2)
		displayQuadTree(root.TopRight, level+2)
		displayQuadTree(root.BottomLeft, level+2)
		displayQuadTree(root.BottomRight, level+2)
	}
}

func Construct_quad_tree() {
	s := [][]int{
		[]int{0, 1},
		[]int{1, 0},
	}
	displayQuadTree(construct(s), 0)
}
