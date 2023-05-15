package swapping_nodes_in_a_linked_list

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func swapNodesHelper(head *ListNode, k int, first **ListNode, second **ListNode, n int) int {
	if head == nil {
		return 0
	} else {
		if n == k {
			*first = head
		}
		r := swapNodesHelper(head.Next, k, first, second, n+1) + 1
		if r == k {
			*second = head
		}
		return r
	}
}

func swapNodes(head *ListNode, k int) *ListNode {
	var first *ListNode
	var second *ListNode
	swapNodesHelper(head, k, &first, &second, 1)
	firstValue := first.Val
	secondValue := second.Val
	first.Val = secondValue
	second.Val = firstValue
	return head
}

func Main() {
	a := ListNode{1, nil}
	b := ListNode{2, nil}
	c := ListNode{3, nil}
	d := ListNode{4, nil}
	e := ListNode{5, nil}
	a.Next = &b
	b.Next = &c
	c.Next = &d
	d.Next = &e
	answer := swapNodes(&a, 2)
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
