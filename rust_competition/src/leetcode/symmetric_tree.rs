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
    pub fn is_mirror(
        left: &Option<Rc<RefCell<TreeNode>>>,
        right: &Option<Rc<RefCell<TreeNode>>>,
    ) -> bool {
        if let Some(left) = left {
            if let Some(right) = right {
                let left = left.borrow();
                let right = right.borrow();
                return left.val == right.val
                    && Self::is_mirror(&left.left, &right.right)
                    && Self::is_mirror(&left.right, &right.left);
            } else {
                return false;
            }
        } else {
            return right.is_none();
        }
    }
    pub fn is_symmetric(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        if let Some(root) = root {
            let root = root.borrow();
            return Self::is_mirror(&root.left, &root.right);
        } else {
            return true;
        }
    }
}

struct Solution {}

pub fn symmetric_tree() {
    let a = TreeNode::new(3);
    let mut b = TreeNode::new(2);
    let c = TreeNode::new(4);
    let mut d = TreeNode::new(1);
    let e = TreeNode::new(4);
    let mut f = TreeNode::new(2);
    let g = TreeNode::new(3);
    b.left = Some(Rc::new(RefCell::new(a)));
    b.right = Some(Rc::new(RefCell::new(c)));
    f.left = Some(Rc::new(RefCell::new(e)));
    f.right = Some(Rc::new(RefCell::new(g)));
    d.left = Some(Rc::new(RefCell::new(b)));
    d.right = Some(Rc::new(RefCell::new(f)));
    let answer = Solution::is_symmetric(Some(Rc::new(RefCell::new(d))));
    println!("{}", answer);
}
