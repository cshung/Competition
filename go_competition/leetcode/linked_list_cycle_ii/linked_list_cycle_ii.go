package linked_list_cycle_ii

import "fmt"

// Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

func detectCycle(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}
	slow := head
	fast := head
	for fast != nil && fast.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
		if slow == fast {
			break
		}
	}
	if fast == nil || fast.Next == nil {
		return nil
	} else {
		slow = head
		for {
			if slow == fast {
				return slow
			}
			slow = slow.Next
			fast = fast.Next
		}
	}
}

func Linked_list_cycle_ii() {
	a := ListNode{3, nil}
	b := ListNode{2, nil}
	c := ListNode{0, nil}
	d := ListNode{4, nil}
	a.Next = &b
	b.Next = &c
	c.Next = &d
	d.Next = &b
	e := detectCycle(&a)
	fmt.Println(e.Val)
}
