use std::collections::VecDeque;
use std::convert::TryInto;

impl Solution {
    pub fn longest_path(parent: Vec<i32>, s: String) -> i32 {
        let labels = s.as_bytes();
        let n = parent.len();
        let mut adj_list: Vec<Vec<usize>> = vec![];
        for _ in 0..n {
            adj_list.push(vec![]);
        }
        for i in 0..n {
            if parent[i] >= 0 {
                let p = parent[i].try_into().unwrap();
                if labels[i] != labels[p] {
                    adj_list[i].push(p);
                    adj_list[p].push(i);
                }
            }
        }
        let mut dist1 = vec![-1; n];
        let mut dist2 = vec![-1; n];
        let mut max = 0;
        for i in 0..n {
            if dist2[i] == -1 {
                dist1[i] = 0;
                let mut bfs = VecDeque::from([i]);
                let mut last = 0;
                while bfs.len() > 0 {
                    let cur = bfs.pop_front().unwrap();
                    last = cur;
                    for rn in &adj_list[cur] {
                        let n = *rn;
                        if dist1[n] == -1 {
                            dist1[n] = dist1[cur] + 1;
                            bfs.push_back(n);
                        }
                    }
                }
                bfs.push_back(last);
                dist2[last] = 0;
                while bfs.len() > 0 {
                    let cur = bfs.pop_front().unwrap();
                    last = cur;
                    for rn in &adj_list[cur] {
                        let n = *rn;
                        if dist2[n] == -1 {
                            dist2[n] = dist2[cur] + 1;
                            bfs.push_back(n);
                        }
                    }
                }
                if dist2[last] > max {
                    max = dist2[last];
                }
            }
        }
        return max + 1;
    }
}

struct Solution {}

pub fn longest_path_with_different_adjacent_characters() {
    let answer = Solution::longest_path(vec![-1, 0, 0, 1, 1, 2], "abacbe".to_string());
    println!("{}", answer);
}
