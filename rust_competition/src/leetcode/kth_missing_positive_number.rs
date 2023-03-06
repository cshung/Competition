impl Solution {
    pub fn find_kth_positive(arr: Vec<i32>, k: i32) -> i32 {
        let mut i = 0;
        let mut j = 0;
        for test in 1..2001 {
            if arr[i] == test {
                i = i + 1;
            } else {
                j = j + 1;
                if j == k {
                    return test;
                }
            }
        }
        // Should not happen
        return -1;
    }
}

struct Solution {}

pub fn kth_missing_positive_number() {
    let answer = Solution::find_kth_positive(vec![2, 3, 4, 7, 11], 5);
    println!("{}", answer);
}
