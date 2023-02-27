use std::cell::RefCell;
use std::rc::Rc;

//Definition for a quad tree node.

#[derive(Debug, PartialEq, Eq)]
pub struct QuadTreeNode {
    pub val: bool,
    pub is_leaf: bool,
    pub top_left: Option<Rc<RefCell<QuadTreeNode>>>,
    pub top_right: Option<Rc<RefCell<QuadTreeNode>>>,
    pub bottom_left: Option<Rc<RefCell<QuadTreeNode>>>,
    pub bottom_right: Option<Rc<RefCell<QuadTreeNode>>>,
}

impl Solution {
    pub fn construct(grid: Vec<Vec<i32>>) -> Option<Rc<RefCell<QuadTreeNode>>> {
        let n = grid.len();
        let mut sums = vec![vec![0; n + 1]; n + 1];
        for i in 0..n {
            for j in 0..n {
                sums[i + 1][j + 1] = grid[i][j] + sums[i][j + 1] + sums[i + 1][j] - sums[i][j];
            }
        }
        return Self::construct_helper(&sums, 0, 0, n, n);
    }

    fn construct_helper(
        sums: &Vec<Vec<i32>>,
        r1: usize,
        c1: usize,
        r2: usize,
        c2: usize,
    ) -> Option<Rc<RefCell<QuadTreeNode>>> {
        let size = ((r2 - r1) * (c2 - c1)) as i32;
        let sum = sums[r2][c2] - sums[r2][c1] - sums[r1][c2] + sums[r1][c1];
        let node: QuadTreeNode;
        if sum == 0 {
            node = QuadTreeNode {
                val: false,
                is_leaf: true,
                top_left: None,
                top_right: None,
                bottom_left: None,
                bottom_right: None,
            };
        } else if sum == size {
            node = QuadTreeNode {
                val: true,
                is_leaf: true,
                top_left: None,
                top_right: None,
                bottom_left: None,
                bottom_right: None,
            };
        } else {
            let mid_r = (r1 + r2) / 2;
            let mid_c = (c1 + c2) / 2;
            node = QuadTreeNode {
                val: false,
                is_leaf: false,
                top_left: Self::construct_helper(sums, r1, c1, mid_r, mid_c),
                top_right: Self::construct_helper(sums, r1, mid_c, mid_r, c2),
                bottom_left: Self::construct_helper(sums, mid_r, c1, r2, mid_c),
                bottom_right: Self::construct_helper(sums, mid_r, mid_c, r2, c2),
            }
        }
        return Some(Rc::new(RefCell::new(node)));
    }
}

fn display_quad_tree(root: Option<Rc<RefCell<QuadTreeNode>>>, level: usize) {
    if let Some(root) = root {
        let root = root.borrow();
        if root.is_leaf {
            for _ in 0..level {
                print!(" ");
            }
            println!("{}", if root.val { 1 } else { 0 });
        } else {
            display_quad_tree(root.top_left.clone(), level + 2);
            display_quad_tree(root.top_right.clone(), level + 2);
            display_quad_tree(root.bottom_left.clone(), level + 2);
            display_quad_tree(root.bottom_right.clone(), level + 2);
        }
    }
}

struct Solution {}

pub fn construct_quad_tree() {
    display_quad_tree(Solution::construct(vec![vec![1, 0], vec![0, 1]]), 0);
}
