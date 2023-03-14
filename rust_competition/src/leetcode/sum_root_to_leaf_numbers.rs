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
    pub fn sum_numbers_helper(val: i32, root: &Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if let Some(root) = root {
            let root = root.borrow();
            let next_val = val * 10 + root.val;
            let mut leaf = true;
            let mut answer = 0;
            if let Some(_) = &root.left {
                leaf = false;
                answer = answer + Self::sum_numbers_helper(next_val, &root.left);
            }
            if let Some(_) = &root.right {
                leaf = false;
                answer = answer + Self::sum_numbers_helper(next_val, &root.right);
            }
            if leaf {
                answer = answer + next_val;
            }
            return answer;
        } else {
            return 0;
        }
    }

    pub fn sum_numbers(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        return Self::sum_numbers_helper(0, &root);
    }
}

struct Solution {}

pub fn sum_root_to_leaf_numbers() {
    let a = TreeNode::new(2);
    let mut b = TreeNode::new(1);
    let c = TreeNode::new(3);
    b.left = Some(Rc::new(RefCell::new(a)));
    b.right = Some(Rc::new(RefCell::new(c)));
    let answer = Solution::sum_numbers(Some(Rc::new(RefCell::new(b))));
    println!("{}", answer);
}
