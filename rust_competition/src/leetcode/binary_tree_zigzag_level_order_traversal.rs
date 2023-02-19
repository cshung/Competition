use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

//Definition for a binary tree node.
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
    pub fn zigzag_level_order(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<Vec<i32>> {
        let mut buffer1 = VecDeque::new();
        let mut buffer2 = VecDeque::new();
        let mut reverse = false;
        if let Some(root) = root {
            let mut current_level = &mut buffer1;
            let mut next_level = &mut buffer2;
            let mut answer = vec![];
            current_level.push_back(root.clone());
            loop {
                let mut current_answer = vec![];
                while current_level.len() > 0 {
                    let cur = current_level.pop_front().unwrap().clone();
                    let cur = cur.borrow();
                    current_answer.push(cur.val);
                    if let Some(left) = cur.left.clone() {
                        next_level.push_back(left);
                    }
                    if let Some(right) = cur.right.clone() {
                        next_level.push_back(right);
                    }
                }
                if reverse {
                    current_answer.reverse();
                }
                answer.push(current_answer);
                if next_level.len() == 0 {
                    break;
                }
                let temp = current_level;
                current_level = next_level;
                next_level = temp;
                reverse = !reverse;
            }
            return answer;
        } else {
            return vec![];
        }
    }
}

struct Solution {}

pub fn binary_tree_zigzag_level_order_traversal() {
    let n1 = Rc::new(RefCell::new(TreeNode::new(9)));
    let n2 = Rc::new(RefCell::new(TreeNode::new(3)));
    let n3 = Rc::new(RefCell::new(TreeNode::new(15)));
    let n4 = Rc::new(RefCell::new(TreeNode::new(20)));
    let n5 = Rc::new(RefCell::new(TreeNode::new(7)));

    n2.borrow_mut().left = Some(Rc::clone(&n1));
    n2.borrow_mut().right = Some(Rc::clone(&n4));
    n4.borrow_mut().left = Some(Rc::clone(&n3));
    n4.borrow_mut().right = Some(Rc::clone(&n5));
    let rows = Solution::zigzag_level_order(Some(Rc::clone(&n2)));
    for row in rows {
        for elem in row {
            print!("{} ", elem);
        }
        println!();
    }
}
