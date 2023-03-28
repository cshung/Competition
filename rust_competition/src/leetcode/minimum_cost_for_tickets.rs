use std::cmp;

impl Solution {
    pub fn mincost_tickets(days: Vec<i32>, costs: Vec<i32>) -> i32 {
        if days.len() == 0 {
            return 0;
        }
        let mut next_travel_day = days[0] as usize;
        let mut next_day_index = 1;
        let mut best = vec![0; 365 + 30];
        for i in 1..366 {
            if i == next_travel_day {
                best[i + 29] = cmp::min(
                    cmp::min(best[i + 29 - 1] + costs[0], best[i + 29 - 7] + costs[1]),
                    best[i + 29 - 30] + costs[2],
                );
                if next_day_index < days.len() {
                    next_travel_day = days[next_day_index] as usize;
                    next_day_index += 1;
                } else {
                    return best[i + 29];
                }
            } else {
                best[i + 29] = best[i + 28];
            }
        }
        return -1;
    }
}

struct Solution {}

pub fn minimum_cost_for_tickets() {
    let answer = Solution::mincost_tickets(vec![1, 4, 6, 7, 8, 20], vec![2, 7, 15]);
    println!("{}", answer);
}
