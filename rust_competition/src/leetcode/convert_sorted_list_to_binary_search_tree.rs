use std::cell::RefCell;
use std::rc::Rc;

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

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

impl Solution {
    pub fn fill<'a>(
        root: &Option<Rc<RefCell<TreeNode>>>,
        head: &'a Option<Box<ListNode>>,
    ) -> &'a Option<Box<ListNode>> {
        if let Some(root) = root {
            let mut root = root.borrow_mut();
            let head: &'a Option<Box<ListNode>> = Self::fill(&root.left, head);
            let best = head.as_ref().unwrap();
            root.val = best.val;
            let head = &best.next;
            let head = Self::fill(&root.right, head);
            return head;
        } else {
            return head;
        }
    }

    pub fn sorted_list_to_bst(head: Option<Box<ListNode>>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut cur = &head;
        let mut length = 0;
        loop {
            if let Some(node) = cur {
                cur = &node.next;
                length = length + 1;
            } else {
                break;
            }
        }
        if length == 0 {
            return None;
        }
        let mut nodes = vec![];
        for _i in 0..length {
            nodes.push(Rc::new(RefCell::new(TreeNode::new(0))));
        }
        for i in 0..length {
            let right = (i + 1) * 2;
            let left = right - 1;
            let mut me = nodes[i].borrow_mut();
            if left < nodes.len() {
                me.left = Some(Rc::clone(&nodes[left]));
            }
            if right < nodes.len() {
                me.right = Some(Rc::clone(&nodes[right]));
            }
        }
        Self::fill(&Some(Rc::clone(&nodes[0])), &head);
        return Some(Rc::clone(&nodes[0]));
    }
}

struct Solution {}

pub fn convert_sorted_list_to_binary_search_tree() {
    let mut a = Box::new(ListNode::new(1));
    let mut b = Box::new(ListNode::new(2));
    let c = Box::new(ListNode::new(3));
    b.next = Some(c);
    a.next = Some(b);
    let answer = Solution::sorted_list_to_bst(Some(a)).unwrap();
    let root = answer.borrow();
    let left = root.left.as_ref().unwrap().borrow();
    let right = root.right.as_ref().unwrap().borrow();
    println!("{}", left.val);
    println!("{}", root.val);
    println!("{}", right.val);
}
