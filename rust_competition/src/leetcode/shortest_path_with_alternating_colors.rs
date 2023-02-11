use std::cmp;
use std::collections::VecDeque;

impl Solution {
    pub fn shortest_alternating_paths(
        n: i32,
        red_edges: Vec<Vec<i32>>,
        blue_edges: Vec<Vec<i32>>,
    ) -> Vec<i32> {
        let n = n as usize;
        let mut bfs = VecDeque::new();
        let mut dist = vec![-1; 2 * n];
        let mut edges = vec![vec![]; 2 * n];

        for red_edge in red_edges {
            let src = (red_edge[0] * 2) as usize;
            let dst = (red_edge[1] * 2 + 1) as usize;
            edges[src].push(dst);
        }

        for blue_edge in blue_edges {
            let src = (blue_edge[0] * 2 + 1) as usize;
            let dst = (blue_edge[1] * 2) as usize;
            edges[src].push(dst);
        }

        bfs.push_back(0);
        bfs.push_back(1);
        dist[0] = 0;
        dist[1] = 0;
        while bfs.len() > 0 {
            let cur = bfs.pop_front().unwrap();
            for neighbor in &edges[cur] {
                if dist[*neighbor] == -1 {
                    dist[*neighbor] = dist[cur] + 1;
                    bfs.push_back(*neighbor);
                }
            }
        }

        let mut answer = vec![];
        for i in 0..n {
            let red_dist = dist[2 * i];
            let blue_dist = dist[2 * i + 1];
            if red_dist == -1 {
                answer.push(blue_dist);
            } else if blue_dist == -1 {
                answer.push(red_dist);
            } else {
                answer.push(cmp::min(red_dist, blue_dist));
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn shortest_path_with_alternating_colors() {
    let answers = Solution::shortest_alternating_paths(3, vec![vec![0, 1], vec![1, 2]], vec![]);
    for answer in answers {
        print!("{} ", answer);
    }
    println!();
}
