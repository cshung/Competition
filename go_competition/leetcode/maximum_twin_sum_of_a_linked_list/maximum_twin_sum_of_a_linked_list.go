package maximum_twin_sum_of_a_linked_list

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func max(a int, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

func pairSum(head *ListNode) int {
	values := []int{}
	for head != nil {
		values = append(values, head.Val)
		head = head.Next
	}
	best := 0
	n := len(values)
	for i := 0; i*2 < n; i++ {
		twin_sum := values[i] + values[n-i-1]
		best = max(best, twin_sum)
	}
	return best
}

func Main() {
	a := ListNode{5, nil}
	b := ListNode{4, nil}
	c := ListNode{2, nil}
	d := ListNode{1, nil}
	a.Next = &b
	b.Next = &c
	c.Next = &d
	d.Next = nil
	answer := pairSum(&a)
	fmt.Println(answer)
}
