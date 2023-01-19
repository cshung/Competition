use std::collections::HashMap;

impl Solution {
    pub fn subarrays_div_by_k(nums: Vec<i32>, k: i32) -> i32 {
        let n = nums.len();
        let mut running_sum_residue = 0;
        let mut residue_counts = HashMap::new();
        residue_counts.insert(0, 1);
        for i in 0..n {
            running_sum_residue = (running_sum_residue + nums[i]).rem_euclid(k);
            if let Some(count) = residue_counts.get_mut(&running_sum_residue) {
                *count = *count + 1;
            } else {
                residue_counts.insert(running_sum_residue, 1);
            }
        }

        let mut answer = 0;
        for (_component, count_reference) in &residue_counts {
            let count = *count_reference;
            answer = answer + count * (count - 1) / 2;
        }
        return answer;
    }
}

struct Solution {}

pub fn subarray_sums_divisible_by_k() {
    let answer = Solution::subarrays_div_by_k(vec![4, 5, 0, -2, -3, 1], 5);
    println!("{}", answer);
}
