impl Solution {
    pub fn zero_filled_subarray(nums: Vec<i32>) -> i64 {
        let mut state = 0;
        let mut streak = 0;
        let mut count = 0;
        for i in 0..nums.len() {
            if state == 0 {
                if nums[i] == 0 {
                    state = 1;
                    streak = 1;
                }
            } else if state == 1 {
                if nums[i] == 0 {
                    streak = streak + 1;
                } else {
                    state = 0;
                    count += (streak + 1) * streak / 2;
                }
            }
        }
        if state == 1 {
            count += (streak + 1) * streak / 2;
        }
        return count;
    }
}

struct Solution {}

pub fn number_of_zero_filled_subarrays() {
    let answer = Solution::zero_filled_subarray(vec![1, 3, 0, 0, 2, 0, 0, 4, 0, 0]);
    println!("{}", answer);
}
