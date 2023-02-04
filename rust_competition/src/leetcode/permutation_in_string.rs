use std::collections::HashMap;

impl Solution {
    pub fn check_inclusion(s1: String, s2: String) -> bool {
        let m = s1.len();
        let n = s2.len();
        let c2: Vec<char> = s2.chars().collect();
        if m <= n {
            let mut hist = HashMap::new();
            for c in s1.chars() {
                if let Some(count) = hist.get_mut(&c) {
                    *count = *count + 1;
                } else {
                    hist.insert(c, 1);
                }
            }
            let mut roll = HashMap::new();
            let mut hit_count = 0;
            for i in 0..n {
                let to_add = c2[i];
                let mut new_count;
                let mut old_count;

                if let Some(count) = roll.get_mut(&to_add) {
                    *count = *count + 1;
                    new_count = *count;
                } else {
                    roll.insert(to_add, 1);
                    new_count = 1;
                }
                old_count = new_count - 1;
                if let Some(required_count) = hist.get_mut(&to_add) {
                    if new_count == *required_count {
                        hit_count = hit_count + 1;
                    } else if old_count == *required_count {
                        hit_count = hit_count - 1;
                    }
                }
                if i >= m {
                    let to_remove = c2[i - m];
                    if let Some(count) = roll.get_mut(&to_remove) {
                        *count = *count - 1;
                        new_count = *count;
                    }
                    old_count = new_count + 1;
                    if let Some(required_count) = hist.get_mut(&to_remove) {
                        if new_count == *required_count {
                            hit_count = hit_count + 1;
                        } else if old_count == *required_count {
                            hit_count = hit_count - 1;
                        }
                    }
                }
                if hit_count == hist.len() {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }
}

struct Solution {}

pub fn permutation_in_string() {
    let answer = Solution::check_inclusion("ab".to_string(), "eidbaooo".to_string());
    println!("{}", answer);
}
