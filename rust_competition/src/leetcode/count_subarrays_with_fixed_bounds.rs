use std::cmp;

impl Solution {
    fn process_range(nums: &Vec<i32>, min_k: i32, max_k: i32, start: usize, end: usize) -> i64 {
        let mut left_most_max = None;
        let mut left_most_min = None;
        let length = (end - start) as i64;
        let mut answer = length * (length + 1) / 2;
        for j in start..end {
            let i = start + end - j - 1;
            if nums[i] == min_k {
                left_most_min = Some(i);
            }
            if nums[i] == max_k {
                left_most_max = Some(i);
            }
            let mut last = end;
            if let Some(left_most_min) = left_most_min {
                if let Some(left_most_max) = left_most_max {
                    last = cmp::max(left_most_min, left_most_max);
                }
            }
            answer = answer - ((last - i) as i64);
        }
        return answer;
    }

    pub fn count_subarrays(nums: Vec<i32>, min_k: i32, max_k: i32) -> i64 {
        let mut state = 0;
        let n = nums.len();
        let mut start = 0;
        let mut answer = 0;
        for i in 0..n {
            let v = nums[i];
            let is_in_range = (min_k <= v) && (v <= max_k);
            if state == 0 {
                if is_in_range {
                    start = i;
                    state = 1;
                }
            } else if !is_in_range {
                answer = answer + Self::process_range(&nums, min_k, max_k, start, i);
                state = 0;
            }
        }
        if state == 1 {
            answer = answer + Self::process_range(&nums, min_k, max_k, start, n);
        }
        return answer;
    }
}

struct Solution {}

pub fn count_subarrays_with_fixed_bounds() {
    let answer = Solution::count_subarrays(vec![1, 3, 5, 2, 7, 5], 1, 5);
    println!("{}", answer);
}
