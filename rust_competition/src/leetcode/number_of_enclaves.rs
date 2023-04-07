impl Solution {
    fn dfs(grid: &Vec<Vec<i32>>, visited: &mut Vec<Vec<bool>>, r: usize, c: usize) -> (bool, i32) {
        let height = grid.len();
        let width = grid[0].len();
        let mut invalid = false;
        let mut count = 1;
        visited[r][c] = true;
        if r == 0 {
            invalid = true;
        } else if grid[r - 1][c] == 1 && !visited[r - 1][c] {
            let (invalid_child, child_count) = Self::dfs(grid, visited, r - 1, c);
            invalid = invalid || invalid_child;
            count += child_count;
        }
        if r == height - 1 {
            invalid = true;
        } else if grid[r + 1][c] == 1 && !visited[r + 1][c] {
            let (invalid_child, child_count) = Self::dfs(grid, visited, r + 1, c);
            invalid = invalid || invalid_child;
            count += child_count;
        }
        if c == 0 {
            invalid = true;
        } else if grid[r][c - 1] == 1 && !visited[r][c - 1] {
            let (invalid_child, child_count) = Self::dfs(grid, visited, r, c - 1);
            invalid = invalid || invalid_child;
            count += child_count;
        }
        if c == width - 1 {
            invalid = true;
        } else if grid[r][c + 1] == 1 && !visited[r][c + 1] {
            let (invalid_child, child_count) = Self::dfs(grid, visited, r, c + 1);
            invalid = invalid || invalid_child;
            count += child_count;
        }
        return (invalid, count);
    }
    pub fn num_enclaves(grid: Vec<Vec<i32>>) -> i32 {
        let height = grid.len();
        let width = grid[0].len();
        let mut visited = vec![vec![false; width]; height];
        let mut answer = 0;
        for r in 0..height {
            for c in 0..width {
                if grid[r][c] == 1 && !visited[r][c] {
                    let (invalid, count) = Self::dfs(&grid, &mut visited, r, c);
                    if !invalid {
                        answer += count;
                    }
                }
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn number_of_enclaves() {
    let answer = Solution::num_enclaves(vec![
        vec![0, 0, 0, 0],
        vec![1, 0, 1, 0],
        vec![0, 1, 1, 0],
        vec![0, 0, 0, 0],
    ]);
    println!("{}", answer);
}
