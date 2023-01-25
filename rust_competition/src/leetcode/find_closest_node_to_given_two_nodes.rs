use std::cmp;
use std::collections::VecDeque;
use std::convert::TryInto;

impl Solution {
    pub fn closest_meeting_node(edges: Vec<i32>, node1: i32, node2: i32) -> i32 {
        let n = edges.len();
        let mut bfs = VecDeque::new();
        let snode1: usize = node1.try_into().unwrap();
        let snode2: usize = node2.try_into().unwrap();
        let mut dist1 = vec![-1; n];
        let mut dist2 = vec![-1; n];

        bfs.push_back(snode1);
        dist1[snode1] = 0;
        while bfs.len() > 0 {
            let cur = bfs.pop_front().unwrap();
            let neighbor = edges[cur];
            if neighbor != -1 {
                let sn = neighbor.try_into().unwrap();
                if dist1[sn] == -1 {
                    dist1[sn] = dist1[cur] + 1;
                    bfs.push_back(sn);
                }
            }
        }

        bfs.push_back(snode2);
        dist2[snode2] = 0;
        while bfs.len() > 0 {
            let cur = bfs.pop_front().unwrap();
            let neighbor = edges[cur];
            if neighbor != -1 {
                let sn = neighbor.try_into().unwrap();
                if dist2[sn] == -1 {
                    dist2[sn] = dist2[cur] + 1;
                    bfs.push_back(sn);
                }
            }
        }
        let mut best_node = -1;
        let mut best_dist = 0;
        for i in 0..n {
            let d1 = dist1[i];
            let d2 = dist2[i];
            if d1 != -1 && d2 != -1 {
                let d = cmp::max(d1, d2);
                if best_node == -1 || d < best_dist {
                    best_node = i.try_into().unwrap();
                    best_dist = d;
                }
            }
        }
        return best_node;
    }
}

struct Solution {}

pub fn find_closest_node_to_given_two_nodes() {
    let answer = Solution::closest_meeting_node(vec![2, 2, 3, -1], 0, 2);
    println!("{}", answer);
}
