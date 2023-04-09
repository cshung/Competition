use std::cmp;

impl Solution {
    fn dfs(
        current: usize,
        colors: &Vec<usize>,
        adjacency_lists: &Vec<Vec<usize>>,
        visited: &mut Vec<i32>,
        max_paths: &mut Vec<Vec<i32>>,
        answer: &mut i32,
    ) -> bool {
        visited[current] = 1;
        for neighbor in &adjacency_lists[current] {
            if visited[*neighbor] == 1 {
                return true;
            } else if visited[*neighbor] == 0 {
                if Self::dfs(
                    *neighbor,
                    colors,
                    adjacency_lists,
                    visited,
                    max_paths,
                    answer,
                ) {
                    return true;
                };
            }
            for c in 0..26 {
                max_paths[current][c] = cmp::max(max_paths[current][c], max_paths[*neighbor][c]);
            }
        }

        max_paths[current][colors[current]] += 1;
        *answer = cmp::max(*answer, max_paths[current][colors[current]]);
        visited[current] = 2;
        return false;
    }
    pub fn largest_path_value(colors: String, edges: Vec<Vec<i32>>) -> i32 {
        let n = colors.len();
        let a = 'a' as u8;
        let colors = colors.bytes().map(|n| (n - a) as usize).collect();
        let mut adjacency_lists = vec![vec![]; n];
        let mut max_paths = vec![vec![0; 26]; n];
        let mut visited = vec![0; n];
        for edge in edges {
            let src = edge[0] as usize;
            let dst = edge[1] as usize;
            adjacency_lists[src].push(dst);
        }
        let mut answer = 0;
        for i in 0..n {
            if visited[i] == 0 {
                if Self::dfs(
                    i,
                    &colors,
                    &adjacency_lists,
                    &mut visited,
                    &mut max_paths,
                    &mut answer,
                ) {
                    return -1;
                }
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn largest_color_value_in_a_directed_graph() {
    let answer = Solution::largest_path_value(
        "abaca".to_string(),
        vec![vec![0, 1], vec![0, 2], vec![2, 3], vec![3, 4]],
    );
    println!("{}", answer);
}
