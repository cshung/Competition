use std::cmp;

impl Solution {
    fn dfs(
        current: usize,
        visited: &mut Vec<bool>,
        best: &mut Option<i32>,
        roads: &Vec<Vec<i32>>,
        adjacency_lists: &Vec<Vec<usize>>,
    ) {
        visited[current] = true;
        if current < roads.len() {
            let distance = roads[current][2];
            if let Some(best_value) = best {
                *best = Some(cmp::min(*best_value, distance));
            } else {
                *best = Some(distance);
            }
        }
        for neighbor in &adjacency_lists[current] {
            if !visited[*neighbor] {
                Self::dfs(*neighbor, visited, best, roads, adjacency_lists);
            }
        }
    }

    pub fn min_score(n: i32, roads: Vec<Vec<i32>>) -> i32 {
        let n = n as usize;
        let mut adjacency_lists = vec![vec![]; n + roads.len()];
        for r in 0..roads.len() {
            let road = &roads[r];
            let mut src = road[0] as usize;
            let mut dst = road[1] as usize;
            src = src + roads.len() - 1;
            dst = dst + roads.len() - 1;
            adjacency_lists[src].push(r);
            adjacency_lists[dst].push(r);
            adjacency_lists[r].push(src);
            adjacency_lists[r].push(dst);
        }
        let mut best = None;
        let mut visited = vec![false; n + roads.len()];
        Self::dfs(
            roads.len(),
            &mut visited,
            &mut best,
            &roads,
            &adjacency_lists,
        );
        return best.unwrap();
    }
}

struct Solution {}

pub fn minimum_score_of_a_path_between_two_cities() {
    let answer = Solution::min_score(
        4,
        vec![vec![1, 2, 9], vec![2, 3, 6], vec![2, 4, 5], vec![1, 4, 7]],
    );
    println!("{}", answer);
}
