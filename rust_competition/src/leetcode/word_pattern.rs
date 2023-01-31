use std::collections::HashMap;

impl Solution {
    pub fn word_pattern(pattern: String, s: String) -> bool {
        let mut word_to_pattern = HashMap::new();
        let mut pattern_to_word = HashMap::new();
        let split = s.split(" ");
        let mut i = 0;
        let pattern_bytes = pattern.as_bytes();
        for s in split {
            if i >= pattern_bytes.len() {
                return false;
            }
            let actual_byte = pattern_bytes[i];
            if let Some(expected_byte) = word_to_pattern.get(s) {
                if *expected_byte != actual_byte {
                    return false;
                }
            } else {
                if let Some(_) = pattern_to_word.get(&actual_byte) {
                    return false;
                } else {
                    word_to_pattern.insert(s.to_string(), actual_byte);
                    pattern_to_word.insert(actual_byte, s.to_string());
                }
            }
            i = i + 1;
        }
        return i == pattern_bytes.len();
    }
}

struct Solution {}

pub fn word_pattern() {
    let answer = Solution::word_pattern("abba".to_string(), "dog cat cat fish".to_string());
    println!("{}", answer);
}
