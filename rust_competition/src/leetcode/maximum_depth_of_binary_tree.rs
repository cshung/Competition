use std::cell::RefCell;
use std::rc::Rc;

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
    pub fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if let Some(root) = root {
            let left_depth = Self::max_depth(root.borrow().left.clone());
            let right_depth = Self::max_depth(root.borrow().right.clone());
            return 1 + left_depth.max(right_depth);
        } else {
            return 0;
        }
    }
}

struct Solution {}

pub fn maximum_depth_of_binary_tree() {
    let n1 = Rc::new(RefCell::new(TreeNode::new(9)));
    let n2 = Rc::new(RefCell::new(TreeNode::new(3)));
    let n3 = Rc::new(RefCell::new(TreeNode::new(15)));
    let n4 = Rc::new(RefCell::new(TreeNode::new(20)));
    let n5 = Rc::new(RefCell::new(TreeNode::new(7)));
    n2.borrow_mut().left = Some(Rc::clone(&n1));
    n2.borrow_mut().right = Some(Rc::clone(&n4));
    n4.borrow_mut().left = Some(Rc::clone(&n3));
    n4.borrow_mut().right = Some(Rc::clone(&n5));
    let answer = Solution::max_depth(Some(Rc::clone(&n2)));
    println!("{}", answer);
}
