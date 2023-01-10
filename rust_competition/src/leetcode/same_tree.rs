use std::cell::RefCell;
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
    pub fn is_same_tree(
        p: Option<Rc<RefCell<TreeNode>>>,
        q: Option<Rc<RefCell<TreeNode>>>,
    ) -> bool {
        if let Some(pn) = p {
            if let Some(qn) = q {
                let bpn = pn.borrow();
                let bqn = qn.borrow();
                return (bpn.val == bqn.val)
                    && Self::is_same_tree(bpn.left.clone(), bqn.left.clone())
                    && Self::is_same_tree(bpn.right.clone(), bqn.right.clone());
            } else {
                return false;
            }
        } else {
            return q == None;
        }
    }
}

struct Solution {}

pub fn same_tree() {
    let n1 = Rc::new(RefCell::new(TreeNode::new(1)));
    let n2 = Rc::new(RefCell::new(TreeNode::new(2)));
    let n3 = Rc::new(RefCell::new(TreeNode::new(3)));
    let n4 = Rc::new(RefCell::new(TreeNode::new(1)));
    let n5 = Rc::new(RefCell::new(TreeNode::new(2)));
    let n6 = Rc::new(RefCell::new(TreeNode::new(3)));

    n1.borrow_mut().left = Some(Rc::clone(&n2));
    n1.borrow_mut().right = Some(Rc::clone(&n3));
    n4.borrow_mut().left = Some(Rc::clone(&n5));
    n4.borrow_mut().right = Some(Rc::clone(&n6));

    let answer = Solution::is_same_tree(Some(n1.clone()), Some(n4.clone()));
    println!("{}", answer);
}
