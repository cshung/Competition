use std::collections::HashMap;
use std::collections::HashSet;

impl Solution {
    pub fn distinct_names(ideas: Vec<String>) -> i64 {
        let mut by_tail: HashMap<String, HashSet<usize>> = HashMap::new();
        let mut num_tails_by_head = vec![0; 26];
        let mut intersection_count = vec![vec![0; 26]; 26];
        for idea in ideas {
            let tail = idea[1..].to_string();
            let head = idea.chars().next().unwrap();
            let head = ((head as u8) - ('a' as u8)) as usize;
            if !by_tail.contains_key(&tail) {
                by_tail.insert(tail.clone(), HashSet::new());
            }
            if let Some(heads) = by_tail.get_mut(&tail) {
                heads.insert(head);
            }
            num_tails_by_head[head] = num_tails_by_head[head] + 1;
        }
        for (_t, cs) in by_tail {
            for c1 in &cs {
                for c2 in &cs {
                    intersection_count[*c1][*c2] = intersection_count[*c1][*c2] + 1;
                }
            }
        }
        let mut count = 0;
        for i in 0..26 {
            for j in 0..26 {
                let ci = num_tails_by_head[i];
                let cj = num_tails_by_head[j];
                let cij = intersection_count[i][j];
                count = count + (ci - cij) * (cj - cij);
            }
        }
        return count;
    }
}

struct Solution {}

pub fn naming_a_company() {
    let answer = Solution::distinct_names(vec![
        "coffee".to_string(),
        "donuts".to_string(),
        "time".to_string(),
        "toffee".to_string(),
    ]);
    println!("{}", answer);
}
