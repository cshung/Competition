use std::rc::Rc;
use std::cell::RefCell;

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
      right: None
    }
  }
}

impl Solution {
    fn preorder_traversal_helper(root: &Option<Rc<RefCell<TreeNode>>>, answer: &mut Vec<i32>) {
        match root {
            Some(node) => 
            {
                let n = node.borrow();
                answer.push(n.val);
                Self::preorder_traversal_helper(&n.left, answer);
                Self::preorder_traversal_helper(&n.right, answer);
            },
            None => 
            {
            },
        }
    }
    pub fn preorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = vec![];
        Self::preorder_traversal_helper(&root, &mut result);
        return result;
    }
}

struct Solution
{
}

pub fn binary_tree_preorder_traversal()
{
    let n3 = Rc::new(RefCell::new(TreeNode::new(3)));
    let n2 = Rc::new(RefCell::new(TreeNode::new(2)));
    let n1 = Rc::new(RefCell::new(TreeNode::new(1)));
    n1.borrow_mut().right = Some(Rc::clone(&n2));
    n2.borrow_mut().left = Some(Rc::clone(&n3));
    let answers = Solution::preorder_traversal(Some(Rc::clone(&n1)));
    for answer in answers
    {
        println!("{}", answer);
    }
}