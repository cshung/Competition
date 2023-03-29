impl Solution {
    pub fn max_satisfaction(satisfaction: Vec<i32>) -> i32 {
        let mut satisfaction = satisfaction.clone();
        satisfaction.sort();
        let n = satisfaction.len();
        let mut suffix_sum = vec![0; n + 1];
        let mut answer = satisfaction[n - 1] * (n as i32);
        suffix_sum[n - 1] = satisfaction[n - 1];
        for i in (0..(n - 1)).rev() {
            suffix_sum[i] = satisfaction[i] + suffix_sum[i + 1];
            answer += satisfaction[i] * ((i + 1) as i32);
        }
        for i in 0..n {
            let delta = satisfaction[i] + suffix_sum[i + 1];
            if delta < 0 {
                answer -= delta
            } else {
                break;
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn reducing_dishes() {
    let answer = Solution::max_satisfaction(vec![-1, -8, 0, 5, -9]);
    println!("{}", answer);
}
