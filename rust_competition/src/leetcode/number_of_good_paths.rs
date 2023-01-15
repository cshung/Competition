use std::collections::HashMap;
use std::convert::TryInto;

impl Solution {
    fn find_set(c: i16, s: &mut Vec<i16>) -> i16 {
        let uc: usize = c.try_into().unwrap();
        if s[uc] < 0 {
            return c;
        } else {
            s[uc] = Self::find_set(s[uc], s);
            return s[uc];
        }
    }

    fn union_set(c1: i16, c2: i16, s: &mut Vec<i16>) {
        let d1 = Self::find_set(c1, s);
        let d2 = Self::find_set(c2, s);
        if d1 != d2 {
            let ud1: usize = d1.try_into().unwrap();
            let ud2: usize = d2.try_into().unwrap();
            let size1 = -s[ud1];
            let size2 = -s[ud2];
            let total = size1 + size2;
            if size1 > size2 {
                s[ud2] = d1;
                s[ud1] = -total;
            } else {
                s[ud1] = d2;
                s[ud2] = -total;
            }
        }
    }

    pub fn number_of_good_paths(vals: Vec<i32>, edges: Vec<Vec<i32>>) -> i32 {
        // Step 1: Prepare the adjacency list
        let mut answer = 0;
        let n = vals.len();
        let mut adj_list = vec![];
        for _ in 0..n {
            adj_list.push(vec![]);
        }
        for edge in edges {
            let from: usize = edge[0].try_into().unwrap();
            let to: usize = edge[1].try_into().unwrap();
            adj_list[from].push(to);
            adj_list[to].push(from);
        }

        // Step 3: Sort and bucket nodes by value
        let mut sorted = vals.clone();
        sorted.sort();
        let mut nodes_by_val: HashMap<i32, Vec<usize>> = HashMap::new();
        for i in 0..n {
            let val = vals[i];
            if let Some(nodes) = nodes_by_val.get_mut(&val) {
                (*nodes).push(i)
            } else {
                nodes_by_val.insert(val, vec![i]);
            }
        }

        // Step 3: Prepare disjoint set union find for the forest
        let mut s = vec![-1; n];

        // Step 4: Incrementally add small nodes into the forest and counts
        for i in 0..sorted.len() {
            if (i == 0) || (sorted[i] != sorted[i - 1]) {
                let current_val = sorted[i];
                let nodes = nodes_by_val.get(&current_val).unwrap();

                // Step 4.1 Add the nodes into the forest
                for node in nodes {
                    for neighbor in &adj_list[*node] {
                        let neighbor_val = vals[*neighbor];
                        if neighbor_val <= current_val {
                            Self::union_set(
                                (*node).try_into().unwrap(),
                                (*neighbor).try_into().unwrap(),
                                &mut s,
                            );
                        }
                    }
                }

                // Step 4.2 Counting
                let mut count_by_component = HashMap::new();
                for node in nodes {
                    let node_component = Self::find_set((*node).try_into().unwrap(), &mut s);
                    if let Some(count) = count_by_component.get_mut(&node_component) {
                        *count = *count + 1;
                    } else {
                        count_by_component.insert(node_component, 1);
                    }
                }
                for (_component, count_reference) in &count_by_component {
                    let count = *count_reference;
                    answer = answer + count * (count + 1) / 2;
                }
            }
        }

        return answer;
    }
}

struct Solution {}

pub fn number_of_good_paths() {
    let answer = Solution::number_of_good_paths(
        vec![1, 3, 2, 1, 3],
        vec![vec![0, 1], vec![0, 2], vec![2, 3], vec![2, 4]],
    );
    println!("{}", answer);
}
