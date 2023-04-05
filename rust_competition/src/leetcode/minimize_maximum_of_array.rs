impl Solution {
    pub fn minimize_array_value(nums: Vec<i32>) -> i32 {
        let mut prefix_max = nums[0] as i64;
        let mut prefix_space = 0;
        for i in 1..nums.len() {
            let val = nums[i] as i64;
            let i = i as i64;
            if val > prefix_max {
                let excess = val - prefix_max;
                if prefix_space < excess {
                    let flood = excess - prefix_space;
                    let prefix_length = i + 1;
                    let quotient = flood / prefix_length;
                    let remainder = flood % prefix_length;
                    prefix_max += quotient;
                    if remainder == 0 {
                        prefix_space = 0;
                    } else {
                        prefix_max += 1;
                        prefix_space = prefix_length - remainder;
                    }
                } else {
                    prefix_space -= excess;
                }
            } else {
                prefix_space += prefix_max - val;
            }
        }
        return prefix_max as i32;
    }
}

struct Solution {}

pub fn minimize_maximum_of_array() {
    let answer = Solution::minimize_array_value(vec![3, 7, 1, 6]);
    println!("{}", answer);
}
