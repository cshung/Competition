use std::cmp;

impl Solution {
    pub fn longest_cycle(edges: Vec<i32>) -> i32 {
        let n = edges.len();
        let mut visiting_time = vec![0; n];
        let mut answer = -1;
        let mut time = 1;
        for s in 0..n {
            let mut i = s;
            if visiting_time[i] == 0 {
                visiting_time[i] = time;
                let start_time = time;
                loop {
                    time += 1;
                    let neighbor = edges[i];
                    if neighbor == -1 {
                        break;
                    } else {
                        let neighbor = neighbor as usize;
                        let current_neighbor_time = visiting_time[neighbor];
                        if current_neighbor_time == 0 {
                            visiting_time[neighbor] = time;
                            i = neighbor;
                        } else if current_neighbor_time >= start_time {
                            answer =
                                cmp::max(answer, visiting_time[i] - visiting_time[neighbor] + 1);
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn longest_cycle_in_a_graph() {
    let answer = Solution::longest_cycle(vec![3, 3, 4, 2, 3]);
    println!("{}", answer);
}
