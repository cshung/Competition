use std::cmp;

impl Solution {
    pub fn max_subarray_sum_circular(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut l_max = nums[0];
        let mut l_min = nums[0];
        let mut max = nums[0];
        let mut min = nums[0];
        let mut sum = nums[0];
        for i in 1..n {
            sum = sum + nums[i];
            if l_max > 0 {
                l_max = l_max + nums[i];
            } else {
                l_max = nums[i];
            }
            if l_min < 0 {
                l_min = l_min + nums[i];
            } else {
                l_min = nums[i];
            }
            max = cmp::max(max, l_max);
            min = cmp::min(min, l_min);
        }

        if min == sum {
            return max;
        } else {
            return cmp::max(max, sum - min);
        }
    }
}

struct Solution {}

pub fn maximum_sum_circular_subarray() {
    let answer = Solution::max_subarray_sum_circular(vec![5, -3, 5]);
    println!("{}", answer);
}
