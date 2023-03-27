use std::cmp;

impl Solution {
    pub fn min_path_sum(grid: Vec<Vec<i32>>) -> i32 {
        let num_rows = grid.len();
        let num_cols = grid[0].len();
        let mut best = vec![vec![0; num_cols]; num_rows];
        for row in 0..num_rows {
            for col in 0..num_cols {
                let mut cur = grid[row][col];
                if row == 0 {
                    if col > 0 {
                        cur += best[0][col - 1];
                    }
                } else if col == 0 {
                    cur += best[row - 1][0];
                } else {
                    cur += cmp::min(best[row - 1][col], best[row][col - 1]);
                }
                best[row][col] = cur;
            }
        }
        return best[num_rows - 1][num_cols - 1];
    }
}

struct Solution {}

pub fn minimum_path_sum() {
    let answer = Solution::min_path_sum(vec![vec![1, 3, 1], vec![1, 5, 1], vec![4, 2, 1]]);
    println!("{}", answer);
}
