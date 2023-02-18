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
    pub fn invert_tree(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        if let Some(root) = root {
            let left = root.borrow().left.clone();
            let right = root.borrow().right.clone();
            root.borrow_mut().left = Self::invert_tree(right);
            root.borrow_mut().right = Self::invert_tree(left);
            return Some(root);
        } else {
            return None;
        }
    }
}

struct Solution {}

fn print_tree(root: Option<Rc<RefCell<TreeNode>>>, indent: i32) {
    if let Some(root) = root {
        let left = root.borrow().left.clone();
        let right = root.borrow().right.clone();
        print_tree(right, indent + 2);
        for _ in 0..indent {
            print!(" ");
        }
        print!("{}\n", root.borrow().val);
        print_tree(left, indent + 2);
    }
}

pub fn invert_binary_tree() {
    let n1 = Rc::new(RefCell::new(TreeNode::new(1)));
    let n2 = Rc::new(RefCell::new(TreeNode::new(2)));
    let n3 = Rc::new(RefCell::new(TreeNode::new(3)));
    let n4 = Rc::new(RefCell::new(TreeNode::new(4)));
    let n5 = Rc::new(RefCell::new(TreeNode::new(6)));
    let n6 = Rc::new(RefCell::new(TreeNode::new(7)));
    let n7 = Rc::new(RefCell::new(TreeNode::new(9)));
    n4.borrow_mut().left = Some(Rc::clone(&n2));
    n4.borrow_mut().right = Some(Rc::clone(&n6));
    n2.borrow_mut().left = Some(Rc::clone(&n1));
    n2.borrow_mut().right = Some(Rc::clone(&n3));
    n6.borrow_mut().left = Some(Rc::clone(&n5));
    n6.borrow_mut().right = Some(Rc::clone(&n7));
    let answers = Solution::invert_tree(Some(Rc::clone(&n4)));
    print_tree(answers, 0);
}
