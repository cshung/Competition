use std::cmp;

impl Solution {
    pub fn min_eating_speed(piles: Vec<i32>, h: i32) -> i32 {
        let mut lo = 0;
        let mut hi = 0;
        for i in 0..piles.len() {
            hi = cmp::max(hi, piles[i]);
        }
        loop {
            if hi - lo == 1 {
                return hi;
            }
            let mid = lo + (hi - lo) / 2;
            let mut time = 0;
            for i in 0..piles.len() {
                let pile = piles[i];
                if time > h {
                    break;
                } else {
                    time += pile / mid;
                    if pile % mid != 0 {
                        time += 1;
                    }
                }
            }
            let feasible = time <= h;
            if feasible {
                hi = mid;
            } else {
                lo = mid;
            }
        }
    }
}

struct Solution {}

pub fn koko_eating_bananas() {
    let answer = Solution::min_eating_speed(vec![3, 6, 7, 11], 8);
    println!("{}", answer);
}
