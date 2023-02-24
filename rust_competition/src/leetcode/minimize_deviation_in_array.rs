use std::cmp;
use std::collections::BinaryHeap;

impl Solution {
    pub fn minimum_deviation(nums: Vec<i32>) -> i32 {
        let mut heap = BinaryHeap::new();
        let mut min = None;
        for i in 0..nums.len() {
            let mut n = nums[i];
            if n % 2 == 1 {
                n = n * 2;
            }
            heap.push(n);
            if let Some(min_value) = min {
                min = Some(cmp::min(min_value, n));
            } else {
                min = Some(n);
            }
        }
        let mut min = min.unwrap();
        let mut best = None;
        loop {
            let max = heap.pop().unwrap();
            if let Some(best_value) = best {
                best = Some(cmp::min(best_value, max - min));
            } else {
                best = Some(max - min);
            }
            if max % 2 == 0 {
                let half = max / 2;
                min = cmp::min(half, min);
                heap.push(half);
            } else {
                break;
            }
        }
        return best.unwrap();
    }
}

struct Solution {}

pub fn minimize_deviation_in_array() {
    let answer = Solution::minimum_deviation(vec![1, 2, 3, 4]);
    println!("{}", answer);
}
