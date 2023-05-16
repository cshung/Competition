package swap_nodes_in_pairs

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func swapPairs(head *ListNode) *ListNode {
	nodes := []*ListNode{}
	for head != nil {
		nodes = append(nodes, head)
		head = head.Next
	}
	for i := 0; i < len(nodes); i += 2 {
		if i+1 < len(nodes) {
			temp := nodes[i]
			nodes[i] = nodes[i+1]
			nodes[i+1] = temp
		}
	}
	for i := 1; i < len(nodes); i++ {
		nodes[i-1].Next = nodes[i]
		nodes[i].Next = nil
	}
	return nodes[0]
}

func Main() {

	a := ListNode{1, nil}
	b := ListNode{2, nil}
	c := ListNode{3, nil}
	d := ListNode{4, nil}
	a.Next = &b
	b.Next = &c
	c.Next = &d
	d.Next = nil
	answer := swapPairs(&a)
	fmt.Print(answer.Val)
	for {
		answer = answer.Next
		if answer == nil {
			break
		}
		fmt.Print(", ")
		fmt.Print(answer.Val)
	}
	fmt.Println()
}
