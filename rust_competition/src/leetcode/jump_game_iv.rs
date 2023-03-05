use std::collections::HashMap;
use std::collections::HashSet;
use std::collections::VecDeque;

impl Solution {
    pub fn min_jumps(arr: Vec<i32>) -> i32 {
        if arr.len() == 1 {
            return 0;
        }

        let num_positions = arr.len();
        let mut value_to_id = HashMap::new();
        for i in 0..num_positions {
            let value = arr[i];
            let n = num_positions + value_to_id.len();
            value_to_id.entry(value).or_insert(n);
        }
        let num_values = value_to_id.len();
        let num_nodes = num_positions + num_values;

        let mut adjacency_list = vec![HashSet::new(); num_nodes];
        for i in 0..num_positions {
            let v = value_to_id.get(&arr[i]).unwrap();
            let v = *v;
            adjacency_list[i].insert(v);
            if i > 0 {
                adjacency_list[i].insert(i - 1);
                adjacency_list[v].insert(i - 1);
            }
            if i < arr.len() - 1 {
                adjacency_list[i].insert(i + 1);
                adjacency_list[v].insert(i + 1);
            }
        }

        let mut bfs = VecDeque::new();
        let mut dist = vec![-1; num_nodes];

        let end_position_node = num_positions - 1;
        let end_value = arr[end_position_node];
        let end_value_node = value_to_id[&end_value];
        dist[0] = 0;
        bfs.push_back(0);
        while bfs.len() > 0 {
            let cur = bfs.pop_front().unwrap();
            let neighbors = &adjacency_list[cur];
            for neighbor in neighbors {
                let neighbor = *neighbor;
                if dist[neighbor] == -1 {
                    dist[neighbor] = dist[cur] + 1;
                    if (neighbor == end_position_node) || (neighbor == end_value_node) {
                        return dist[neighbor];
                    }
                    bfs.push_back(neighbor);
                }
            }
        }
        // should not happen
        return -1;
    }
}
struct Solution {}

pub fn jump_game_iv() {
    let answer = Solution::min_jumps(vec![100, -23, -23, 404, 100, 23, 23, 23, 3, 404]);
    println!("{}", answer);
}
