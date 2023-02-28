use std::cell::RefCell;
use std::collections::HashMap;
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
    pub fn save_subtrees(
        root: Option<Rc<RefCell<TreeNode>>>,
        preorder: &mut Vec<i32>,
        trees: &mut HashMap<Vec<i32>, bool>,
        answers: &mut Vec<Option<Rc<RefCell<TreeNode>>>>,
    ) {
        if let Some(root) = root {
            let start = preorder.len();
            preorder.push(root.borrow().val);
            Self::save_subtrees(root.borrow().left.clone(), preorder, trees, answers);
            Self::save_subtrees(root.borrow().right.clone(), preorder, trees, answers);
            let mut keys = vec![];
            for i in start..preorder.len() {
                keys.push(preorder[i]);
            }
            if let Some(hit) = trees.get_mut(&keys) {
                if *hit {
                    answers.push(Some(root.clone()));
                    *hit = false;
                }
            } else {
                trees.insert(keys, true);
            }
        }
    }
    pub fn find_duplicate_subtrees(
        root: Option<Rc<RefCell<TreeNode>>>,
    ) -> Vec<Option<Rc<RefCell<TreeNode>>>> {
        let mut trees = HashMap::new();
        let mut preorder = vec![];
        let mut answers = vec![];
        Self::save_subtrees(root, &mut preorder, &mut trees, &mut answers);
        return answers;
    }
}

struct Solution {}

pub fn find_duplicate_subtrees() {
    let n1 = Rc::new(RefCell::new(TreeNode::new(1)));
    let n2 = Rc::new(RefCell::new(TreeNode::new(1)));
    let n3 = Rc::new(RefCell::new(TreeNode::new(1)));
    n2.borrow_mut().left = Some(Rc::clone(&n1));
    n2.borrow_mut().right = Some(Rc::clone(&n3));
    let answers = Solution::find_duplicate_subtrees(Some(Rc::clone(&n2)));
    for _ in answers {
        println!("Fuck");
    }
}
