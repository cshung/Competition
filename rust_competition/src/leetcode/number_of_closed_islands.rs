impl Solution {
    fn dfs(grid: &Vec<Vec<i32>>, visited: &mut Vec<Vec<bool>>, r: usize, c: usize) -> bool {
        let height = grid.len();
        let width = grid[0].len();
        let mut answer = false;
        visited[r][c] = true;
        if r == 0 {
            answer = true;
        } else if grid[r - 1][c] == 0 && !visited[r - 1][c] {
            answer = Self::dfs(grid, visited, r - 1, c) || answer;
        }
        if r == height - 1 {
            answer = true;
        } else if grid[r + 1][c] == 0 && !visited[r + 1][c] {
            answer = Self::dfs(grid, visited, r + 1, c) || answer;
        }
        if c == 0 {
            answer = true;
        } else if grid[r][c - 1] == 0 && !visited[r][c - 1] {
            answer = Self::dfs(grid, visited, r, c - 1) || answer;
        }
        if c == width - 1 {
            answer = true;
        } else if grid[r][c + 1] == 0 && !visited[r][c + 1] {
            answer = Self::dfs(grid, visited, r, c + 1) || answer;
        }
        return answer;
    }
    pub fn closed_island(grid: Vec<Vec<i32>>) -> i32 {
        let height = grid.len();
        let width = grid[0].len();
        let mut visited = vec![vec![false; width]; height];
        let mut answer = 0;
        for r in 0..height {
            for c in 0..width {
                if grid[r][c] == 0 && !visited[r][c] {
                    if !Self::dfs(&grid, &mut visited, r, c) {
                        answer += 1;
                    }
                }
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn number_of_closed_islands() {
    let answer = Solution::closed_island(vec![
        vec![1, 1, 1, 1, 1, 1, 1, 0],
        vec![1, 0, 0, 0, 0, 1, 1, 0],
        vec![1, 0, 1, 0, 1, 1, 1, 0],
        vec![1, 0, 0, 0, 0, 1, 0, 1],
        vec![1, 1, 1, 1, 1, 1, 1, 0],
    ]);
    println!("{}", answer);
}
