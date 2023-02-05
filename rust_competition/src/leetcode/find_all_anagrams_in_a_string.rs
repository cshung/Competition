use std::collections::HashMap;

impl Solution {
    pub fn find_anagrams(s: String, p: String) -> Vec<i32> {
        let m = p.len();
        let n = s.len();
        let c2: Vec<char> = s.chars().collect();
        let mut answers = vec![];
        if m <= n {
            let mut hist = HashMap::new();
            for c in p.chars() {
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
                    answers.push((i + 1 - m) as i32);
                }
            }
            return answers;
        } else {
            return answers;
        }
    }
}

struct Solution {}

pub fn find_all_anagrams_in_a_string() {
    let answers = Solution::find_anagrams("cbaebabacd".to_string(), "abc".to_string());
    for answer in answers {
        println!("{}", answer);
    }
}
