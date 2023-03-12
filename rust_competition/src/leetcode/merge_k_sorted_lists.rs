use std::collections::BinaryHeap;

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

impl Solution {
    pub fn merge_k_lists(lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        let mut pointers: Vec<&Option<Box<ListNode>>> = vec![];
        let mut heap = BinaryHeap::new();
        for i in 0..lists.len() {
            pointers.push(&lists[i]);
            if let Some(head) = pointers[i] {
                heap.push((-head.val, i));
            }
        }
        let mut stack = None;
        while heap.len() > 0 {
            let (neg_val, which_list) = heap.pop().unwrap();
            stack = Some(Box::new(ListNode {
                val: -neg_val,
                next: stack,
            }));
            pointers[which_list] = &pointers[which_list].as_ref().unwrap().next;
            if let Some(head) = pointers[which_list] {
                heap.push((-head.val, which_list));
            }
        }
        let mut answer = None;
        loop {
            if let Some(mut node) = stack {
                stack = node.next;
                node.next = answer;
                answer = Some(node);
            } else {
                break;
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn merge_k_sorted_lists() {
    let mut a = Box::new(ListNode::new(1));
    let mut b = Box::new(ListNode::new(4));
    let mut c = Box::new(ListNode::new(5));
    let mut d = Box::new(ListNode::new(1));
    let mut e = Box::new(ListNode::new(3));
    let mut f = Box::new(ListNode::new(4));
    let mut g = Box::new(ListNode::new(2));
    let mut h = Box::new(ListNode::new(6));
    c.next = None;
    b.next = Some(c);
    a.next = Some(b);

    f.next = None;
    e.next = Some(f);
    d.next = Some(e);

    h.next = None;
    g.next = Some(h);

    let answer = Solution::merge_k_lists(vec![Some(a), Some(d), Some(g)]);

    let mut cursor = &answer;
    loop {
        if let Some(node) = cursor {
            print!("{} ", node.val);
            cursor = &node.next;
        } else {
            break;
        }
    }
    println!();
}
