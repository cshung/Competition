impl Solution {
    pub fn search(nums: Vec<i32>, target: i32) -> i32 {
        let mut lo = 0;
        let mut hi = nums.len();
        loop {
            let len = hi - lo;
            if len == 0 {
                return -1;
            } else {
                let mid = lo + len / 2;
                let mid_val = nums[mid];
                if target < mid_val {
                    hi = mid;
                } else if target == mid_val {
                    return mid as i32;
                } else {
                    lo = mid + 1;
                }
            }
        }
    }
}

struct Solution {}

pub fn binary_search() {
    let answer = Solution::search(vec![-1, 0, 3, 5, 9, 12], 9);
    println!("{}", answer);
}
