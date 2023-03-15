use std::cell::RefCell;
use std::cmp;
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
    fn is_complete_tree_helper(root: &Option<Rc<RefCell<TreeNode>>>) -> (bool, bool, i32) {
        if let Some(root) = root {
            let root = root.borrow();
            let (left_complete, left_full, left_height) = Self::is_complete_tree_helper(&root.left);
            let (right_complete, right_full, right_height) =
                Self::is_complete_tree_helper(&root.right);
            let complete = left_full && right_complete && left_height == right_height
                || left_complete && right_full && left_height == right_height + 1;
            let full = left_full && right_full && left_height == right_height;
            let height = cmp::max(left_height, right_height) + 1;
            return (complete, full, height);
        } else {
            return (true, true, 0);
        }
    }

    pub fn is_complete_tree(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        let (complete, _full, _height) = Self::is_complete_tree_helper(&root);
        return complete;
    }
}

struct Solution {}

pub fn check_completeness_of_a_binary_tree() {
    let a = TreeNode::new(4);
    let mut b = TreeNode::new(2);
    let c = TreeNode::new(5);
    let mut d = TreeNode::new(1);
    let e = TreeNode::new(6);
    let mut f = TreeNode::new(3);

    b.left = Some(Rc::new(RefCell::new(a)));
    b.right = Some(Rc::new(RefCell::new(c)));
    f.left = Some(Rc::new(RefCell::new(e)));
    d.left = Some(Rc::new(RefCell::new(b)));
    d.right = Some(Rc::new(RefCell::new(f)));

    let answer = Solution::is_complete_tree(Some(Rc::new(RefCell::new(d))));
    println!("{}", answer);
}
