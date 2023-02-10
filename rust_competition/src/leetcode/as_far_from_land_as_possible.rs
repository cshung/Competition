use std::cmp;
use std::collections::HashSet;
use std::collections::VecDeque;

impl Solution {
    fn get_neighbors(
        row: usize,
        col: usize,
        height: usize,
        width: usize,
        grid: &Vec<Vec<i32>>,
        neighbors: &mut HashSet<usize>,
    ) {
        let loc = row * width + col + 1;
        if row > 0 && grid[row - 1][col] == 0 {
            neighbors.insert(loc - width);
        }
        if row < height - 1 && grid[row + 1][col] == 0 {
            neighbors.insert(loc + width);
        }
        if col > 0 && grid[row][col - 1] == 0 {
            neighbors.insert(loc - 1);
        }
        if col < width - 1 && grid[row][col + 1] == 0 {
            neighbors.insert(loc + 1);
        }
    }

    pub fn max_distance(grid: Vec<Vec<i32>>) -> i32 {
        let height = grid.len();
        let width = grid[0].len();
        let mut bfs = VecDeque::new();
        let mut dist = vec![-1; height * width + 1];
        bfs.push_back(0);
        dist[0] = 0;
        let mut best = -1;
        while bfs.len() > 0 {
            let cur = bfs.pop_front().unwrap();
            let mut neighbors = HashSet::new();
            if cur == 0 {
                for row in 0..height {
                    for col in 0..width {
                        if grid[row][col] == 1 {
                            Self::get_neighbors(row, col, height, width, &grid, &mut neighbors);
                        }
                    }
                }
            } else {
                let num = cur - 1;
                let row = num / width;
                let col = num % width;
                Self::get_neighbors(row, col, height, width, &grid, &mut neighbors);
            }
            for neighbor in neighbors {
                if dist[neighbor] == -1 {
                    dist[neighbor] = dist[cur] + 1;
                    best = cmp::max(dist[neighbor], best);
                    bfs.push_back(neighbor);
                }
            }
        }

        return best;
    }
}

struct Solution {}

pub fn as_far_from_land_as_possible() {
    let answer = Solution::max_distance(vec![vec![1, 0, 1], vec![0, 0, 0], vec![1, 0, 1]]);
    println!("{}", answer);
}
