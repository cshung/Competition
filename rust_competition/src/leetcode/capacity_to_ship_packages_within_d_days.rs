impl Solution {
    pub fn ship_within_days(weights: Vec<i32>, days: i32) -> i32 {
        let mut lo = 0;
        let mut hi = 0;
        for i in 0..weights.len() {
            hi = hi + weights[i];
        }
        loop {
            if lo + 1 == hi {
                return hi;
            }
            let mid = lo + (hi - lo) / 2;
            let mut carrying = 0;
            let mut required = 1;
            for i in 0..weights.len() {
                if carrying + weights[i] > mid {
                    required = required + 1;
                    if weights[i] > mid {
                        required = days + 1;
                        break;
                    }
                    carrying = weights[i];
                } else {
                    carrying = carrying + weights[i];
                }
            }
            if required > days {
                lo = mid;
            } else {
                hi = mid;
            }
        }
    }
}

struct Solution {}

pub fn capacity_to_ship_packages_within_d_days() {
    let answer = Solution::ship_within_days(vec![1, 2, 3, 1, 1], 4);
    println!("{}", answer);
}
