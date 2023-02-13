impl Solution {
    pub fn count_odds(low: i32, high: i32) -> i32 {
        let count = high - low + 1;
        return count / 2 + (count % 2) * (low % 2);
    }
}

struct Solution {}

pub fn count_odd_numbers_in_an_interval_range() {
    let answer = Solution::count_odds(4, 6);
    println!("{}", answer);
}
