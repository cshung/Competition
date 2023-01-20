use std::collections::HashSet;
use std::convert::TryInto;

impl Solution {
    fn find_subsequences_helper(
        nums: &Vec<i32>,
        prefix: &mut Vec<i32>,
        index: usize,
        answers: &mut Vec<Vec<i32>>,
        seen: &mut HashSet<Vec<i32>>,
    ) {
        let n = nums.len();
        if index == n {
            if prefix.len() > 1 {
                if !seen.contains(prefix) {
                    seen.insert(prefix.clone());
                    answers.push(prefix.clone());
                }
            }
        } else {
            let p = prefix.len();
            if p == 0 || prefix[p - 1] <= nums[index] {
                prefix.push(nums[index].try_into().unwrap());
                Self::find_subsequences_helper(nums, prefix, index + 1, answers, seen);
                prefix.pop();
            }
            Self::find_subsequences_helper(nums, prefix, index + 1, answers, seen);
        }
    }
    pub fn find_subsequences(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut seen = HashSet::new();
        let mut prefix = vec![];
        let mut answers = vec![];
        Self::find_subsequences_helper(&nums, &mut prefix, 0, &mut answers, &mut seen);
        return answers;
    }
}

struct Solution {}

pub fn non_decreasing_subsequences() {
    let answers = Solution::find_subsequences(vec![4, 6, 7, 7]);
    for answer in answers {
        for entry in answer {
            print!("{} ", entry);
        }
        println!();
    }
}
