impl Solution {
    fn has_apple(rect_sums: &Vec<Vec<i32>>, r1: usize, c1: usize, r2: usize, c2: usize) -> bool {
        let count;
        if r1 == 0 {
            if c1 == 0 {
                count = rect_sums[r2][c2];
            } else {
                count = rect_sums[r2][c2] - rect_sums[r2][c1 - 1];
            }
        } else {
            if c1 == 0 {
                count = rect_sums[r2][c2] - rect_sums[r1 - 1][c2];
            } else {
                count = rect_sums[r2][c2] - rect_sums[r2][c1 - 1] - rect_sums[r1 - 1][c2]
                    + rect_sums[r1 - 1][c1 - 1];
            }
        }
        return count != 0;
    }

    fn ways_helper(
        memo: &mut Vec<Vec<Vec<Vec<Vec<i32>>>>>,
        rect_sums: &Vec<Vec<i32>>,
        r1: usize,
        c1: usize,
        r2: usize,
        c2: usize,
        k: usize,
    ) -> i32 {
        if memo[r1][c1][r2][c2][k] != -1 {
            return memo[r1][c1][r2][c2][k];
        }
        if k == 1 {
            if Self::has_apple(rect_sums, r1, c1, r2, c2) {
                return 1;
            } else {
                return 0;
            }
        } else {
            let mut answer = 0;
            if r2 - r1 + 1 > 1 {
                for rc in r1..r2 {
                    if Self::has_apple(rect_sums, r1, c1, rc, c2) {
                        answer += Self::ways_helper(memo, rect_sums, rc + 1, c1, r2, c2, k - 1);
                        answer = answer % 1000000007;
                    }
                }
            }
            if c2 - c1 + 1 > 1 {
                for cc in c1..c2 {
                    if Self::has_apple(rect_sums, r1, c1, r2, cc) {
                        answer += Self::ways_helper(memo, rect_sums, r1, cc + 1, r2, c2, k - 1);
                        answer = answer % 1000000007;
                    }
                }
            }
            memo[r1][c1][r2][c2][k] = answer;
            return answer;
        }
    }

    pub fn ways(pizza: Vec<String>, k: i32) -> i32 {
        let k = k as usize;
        let height = pizza.len();
        let width = pizza[0].len();
        let mut rect_sums = vec![vec![0; width]; height];
        let apple = 'A' as u8;
        for r in 0..pizza.len() {
            let row = pizza[r].as_bytes();
            for c in 0..row.len() {
                let bit = if row[c] == apple { 1 } else { 0 };
                if r == 0 {
                    if c == 0 {
                        rect_sums[r][c] = bit;
                    } else {
                        rect_sums[r][c] = rect_sums[r][c - 1] + bit;
                    }
                } else {
                    if c == 0 {
                        rect_sums[r][c] = rect_sums[r - 1][c] + bit;
                    } else {
                        rect_sums[r][c] = rect_sums[r - 1][c] + rect_sums[r][c - 1]
                            - rect_sums[r - 1][c - 1]
                            + bit;
                    }
                }
            }
        }
        let mut memo = vec![vec![vec![vec![vec![-1; k + 1]; width]; height]; width]; height];
        return Self::ways_helper(&mut memo, &rect_sums, 0, 0, height - 1, width - 1, k);
    }
}

struct Solution {}

pub fn number_of_ways_of_cutting_a_pizza() {
    let answer = Solution::ways(
        vec!["A..".to_string(), "AAA".to_string(), "...".to_string()],
        3,
    );
    println!("{}", answer);
}
