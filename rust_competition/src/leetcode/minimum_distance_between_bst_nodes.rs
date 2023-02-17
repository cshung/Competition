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
    pub fn in_order(root: Option<Rc<RefCell<TreeNode>>>, values: &mut Vec<i32>) {
        if let Some(root) = root {
            Self::in_order(root.borrow().left.clone(), values);
            values.push(root.borrow().val);
            return Self::in_order(root.borrow().right.clone(), values);
        }
    }

    pub fn min_diff_in_bst(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut values = vec![];
        Self::in_order(root, &mut values);
        let mut answer = None;
        for i in 1..values.len() {
            let diff = (values[i - 1] - values[i]).abs();
            if let Some(unwrapped) = answer {
                answer = Some(cmp::min(unwrapped, diff));
            } else {
                answer = Some(diff);
            }
        }
        return answer.unwrap();
    }
}

struct Solution {}

pub fn minimum_distance_between_bst_nodes() {
    let n1 = Rc::new(RefCell::new(TreeNode::new(1)));
    let n2 = Rc::new(RefCell::new(TreeNode::new(2)));
    let n3 = Rc::new(RefCell::new(TreeNode::new(3)));
    let n4 = Rc::new(RefCell::new(TreeNode::new(4)));
    let n5 = Rc::new(RefCell::new(TreeNode::new(6)));
    n2.borrow_mut().left = Some(Rc::clone(&n1));
    n2.borrow_mut().right = Some(Rc::clone(&n3));
    n4.borrow_mut().left = Some(Rc::clone(&n2));
    n4.borrow_mut().right = Some(Rc::clone(&n5));
    let answer = Solution::min_diff_in_bst(Some(n4.clone()));
    println!("{}", answer);
}
