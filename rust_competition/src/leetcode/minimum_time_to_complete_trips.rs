impl Solution {
    pub fn minimum_time(time: Vec<i32>, total_trips: i32) -> i64 {
        let mut lo = 0;
        let mut hi = i64::MAX;
        let total_trips = total_trips as i64;
        loop {
            if hi - lo == 1 {
                return hi;
            }
            let mid = lo + (hi - lo) / 2;
            let mut all_trips = 0;
            for i in 0..time.len() {
                let trips = mid / (time[i] as i64);
                if trips < total_trips {
                    all_trips += trips;
                } else {
                    all_trips = total_trips;
                    break;
                }
            }
            let feasible = all_trips >= total_trips;
            if feasible {
                hi = mid;
            } else {
                lo = mid;
            }
        }
    }
}

struct Solution {}

pub fn minimum_time_to_complete_trips() {
    let answer = Solution::minimum_time(vec![1, 2, 3], 5);
    println!("{}", answer);
}
