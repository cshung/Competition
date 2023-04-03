impl Solution {
    pub fn num_rescue_boats(people: Vec<i32>, limit: i32) -> i32 {
        let mut people = people.clone();
        people.sort();
        let mut lo = 1;
        let mut hi = people.len();
        let mut answer = 0;
        while hi >= lo {
            if hi != lo {
                if people[lo - 1] + people[hi - 1] <= limit {
                    lo += 1;
                }
            }
            hi -= 1;
            answer += 1;
        }
        return answer;
    }
}

struct Solution {}

pub fn boats_to_save_people() {
    let answer = Solution::num_rescue_boats(vec![1, 2], 3);
    println!("{}", answer);
}
