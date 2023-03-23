impl Solution {
    fn dfs(current: usize, visited: &mut Vec<bool>, adjacency_lists: &Vec<Vec<usize>>) {
        visited[current] = true;
        for neighbor in &adjacency_lists[current] {
            if !visited[*neighbor] {
                Self::dfs(*neighbor, visited, adjacency_lists);
            }
        }
    }

    pub fn make_connected(n: i32, connections: Vec<Vec<i32>>) -> i32 {
        let n = n as usize;
        if connections.len() < n - 1 {
            return -1;
        }
        let mut adjacency_lists = vec![vec![]; n];
        for connection in connections {
            let src = connection[0] as usize;
            let dst = connection[1] as usize;
            adjacency_lists[src].push(dst);
            adjacency_lists[dst].push(src);
        }
        let mut visited = vec![false; n];
        let mut num_connected_components = 0;
        for i in 0..n {
            if !visited[i] {
                num_connected_components += 1;
                Self::dfs(i, &mut visited, &adjacency_lists);
            }
        }
        return num_connected_components - 1;
    }
}

struct Solution {}

pub fn number_of_operations_to_make_network_connected() {
    let answer = Solution::make_connected(4, vec![vec![0, 1], vec![0, 2], vec![1, 2]]);
    println!("{}", answer);
}
