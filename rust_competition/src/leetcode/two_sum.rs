use std::convert::TryInto;

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let l = nums.len();
        for i in 0..l {
            for j in i + 1..l {
                let p = nums[i];
                let q = nums[j];
                if p + q == target {
                    let mut answer: Vec<i32> = vec![];
                    answer.push(i.try_into().unwrap());
                    answer.push(j.try_into().unwrap());
                    return answer;
                }
            }
        }
        return nums;
    }
}

struct Solution {}

pub fn two_sum() {
    let answer = Solution::two_sum(vec![2, 7, 11, 15], 9);
    println!("{} {}", answer[0], answer[1]);
}
