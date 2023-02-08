use std::cmp;

impl Solution {
    pub fn jump(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut dp = vec![None; n];
        dp[n - 1] = Some(0);
        for j in 0..(n - 1) {
            let i = n - 2 - j;
            let k = cmp::min(i + nums[i] as usize, n - 1);
            for d in (i + 1)..(k + 1) {
                if let Some(cost) = dp[d] {
                    if let Some(cur) = dp[i] {
                        if cur > (1 + cost) {
                            dp[i] = Some(1 + cost);
                        }
                    } else {
                        dp[i] = Some(1 + cost);
                    }
                }
            }
        }
        return dp[0].unwrap();
    }
}

struct Solution {}

pub fn jump_game_ii() {
    let answer = Solution::jump(vec![2, 3, 1, 1, 4]);
    println!("{}", answer);
}
