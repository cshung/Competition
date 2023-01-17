impl Solution {
    pub fn min_flips_mono_incr(s: String) -> i32 {
        let b = s.as_bytes();
        let n = s.len();
        let mut cost = vec![0; n + 1];
        let mut l = 0;
        for i in 1..(n + 1) {
            if b[i - 1] == ('1' as u8) {
                l = l + 1
            }
            cost[i] = l
        }
        let mut m = cost[n];
        let mut r = 0;
        for j in 0..n {
            let i = n - j;
            if b[i - 1] == ('0' as u8) {
                r = r + 1
            }
            cost[i - 1] = cost[i - 1] + r;
            if cost[i - 1] < m {
                m = cost[i - 1]
            }
        }
        return m;
    }
}

struct Solution {}

pub fn flip_string_to_monotone_increasing() {
    let answer = Solution::min_flips_mono_incr("00110".to_string());
    println!("{}", answer);
}
