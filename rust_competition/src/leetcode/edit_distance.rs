use std::cmp;

impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let word1 = word1.as_bytes();
        let word2 = word2.as_bytes();
        let m = word1.len();
        let n = word2.len();
        let mut costs = vec![vec![0; n + 1]; m + 1];
        for i in 0..(m + 1) {
            costs[i][0] = i;
        }
        for j in 0..(n + 1) {
            costs[0][j] = j;
        }
        for i in 1..(m + 1) {
            for j in 1..(n + 1) {
                if word1[i - 1] == word2[j - 1] {
                    costs[i][j] = costs[i - 1][j - 1];
                } else {
                    costs[i][j] = 1 + cmp::min(
                        cmp::min(costs[i][j - 1], costs[i - 1][j]),
                        costs[i - 1][j - 1],
                    );
                }
            }
        }
        return costs[m][n] as i32;
    }
}

struct Solution {}

pub fn edit_distance() {
    let answer = Solution::min_distance("horse".to_string(), "ros".to_string());
    println!("{}", answer);
}
