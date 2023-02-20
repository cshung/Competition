impl Solution {
    pub fn search_insert(nums: Vec<i32>, target: i32) -> i32 {
        let n = nums.len();
        let mut lo = 0;
        let mut hi = n + 1;
        while lo < hi {
            let mid = lo + (hi - lo) / 2;
            let left = if mid > 0 {
                nums[mid - 1] < target
            } else {
                true
            };
            let right = if mid < n { nums[mid] >= target } else { true };
            if left {
                if right {
                    return mid as i32;
                } else {
                    lo = mid;
                }
            } else {
                hi = mid;
            }
        }
        return -1;
    }
}

struct Solution {}

pub fn search_insert_position() {
    let answer = Solution::search_insert(vec![1, 3, 5, 6], 5);
    println!("{}", answer);
}
