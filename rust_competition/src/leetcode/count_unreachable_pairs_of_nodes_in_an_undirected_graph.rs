impl Solution {
    fn dfs(current: usize, visited: &mut Vec<bool>, adjacency_lists: &Vec<Vec<usize>>) -> i64 {
        let mut count = 1;
        visited[current] = true;
        for neighbor in &adjacency_lists[current] {
            if !visited[*neighbor] {
                count += Self::dfs(*neighbor, visited, adjacency_lists);
            }
        }
        return count;
    }

    pub fn count_pairs(n: i32, edges: Vec<Vec<i32>>) -> i64 {
        let n = n as usize;
        let mut adjacency_lists = vec![vec![]; n];
        for edge in &edges {
            let src = edge[0] as usize;
            let dst = edge[1] as usize;
            adjacency_lists[src].push(dst);
            adjacency_lists[dst].push(src);
        }
        let mut visited = vec![false; n];
        let mut connected_component_sizes = vec![];
        for i in 0..n {
            if !visited[i] {
                connected_component_sizes.push(Self::dfs(i, &mut visited, &adjacency_lists));
            }
        }
        let mut answer = 0;
        for i in 0..connected_component_sizes.len() {
            let n64 = n as i64;
            answer += connected_component_sizes[i] * (n64 - connected_component_sizes[i]);
        }
        return answer / 2;
    }
}

struct Solution {}

pub fn count_unreachable_pairs_of_nodes_in_an_undirected_graph() {
    let answer = Solution::count_pairs(
        7,
        vec![vec![0, 2], vec![0, 5], vec![2, 4], vec![1, 6], vec![5, 4]],
    );
    println!("{}", answer);
}
