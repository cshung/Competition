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

    pub fn print(root: &Option<Rc<RefCell<TreeNode>>>, indent: usize) {
        for _i in 0..indent {
            print!(" ");
        }
        if let Some(root) = root {
            let root = root.borrow();
            println!("{}", root.val);
            Self::print(&root.left, indent + 2);
            Self::print(&root.right, indent + 2);
        } else {
            println!("None");
        }
    }
}

impl Solution {
    pub fn build_tree_helper(
        inorder: &Vec<i32>,
        postorder: &Vec<i32>,
        value_to_position_map: &HashMap<i32, usize>,
        inorder_start: usize,
        inorder_end: usize,
        postorder_start: usize,
        postorder_end: usize,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        if inorder_end > inorder_start {
            let root_val = postorder[postorder_end - 1];
            let root_pos = *value_to_position_map.get(&root_val).unwrap();
            let left_inorder_start = inorder_start;
            let left_inorder_end = root_pos;
            let left_length = left_inorder_end - left_inorder_start;
            let right_inorder_start = root_pos + 1;
            let right_inorder_end = inorder_end;
            let right_length = right_inorder_end - right_inorder_start;
            let left_postorder_start = postorder_start;
            let left_postorder_end = left_postorder_start + left_length;
            let right_postorder_start = left_postorder_end;
            let right_postorder_end = right_postorder_start + right_length;
            let left = Self::build_tree_helper(
                inorder,
                postorder,
                value_to_position_map,
                left_inorder_start,
                left_inorder_end,
                left_postorder_start,
                left_postorder_end,
            );
            let right = Self::build_tree_helper(
                inorder,
                postorder,
                value_to_position_map,
                right_inorder_start,
                right_inorder_end,
                right_postorder_start,
                right_postorder_end,
            );
            let mut root = TreeNode::new(root_val);
            root.left = left;
            root.right = right;
            return Some(Rc::new(RefCell::new(root)));
        } else {
            return None;
        }
    }

    pub fn build_tree(inorder: Vec<i32>, postorder: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut value_to_position_map = HashMap::new();
        for i in 0..inorder.len() {
            value_to_position_map.insert(inorder[i], i);
        }
        return Self::build_tree_helper(
            &inorder,
            &postorder,
            &value_to_position_map,
            0,
            inorder.len(),
            0,
            postorder.len(),
        );
    }
}

struct Solution {}

pub fn construct_binary_tree_from_inorder_and_postorder_traversal() {
    let answer = Solution::build_tree(vec![9, 3, 15, 20, 7], vec![9, 15, 7, 20, 3]);
    TreeNode::print(&answer, 0);
}
