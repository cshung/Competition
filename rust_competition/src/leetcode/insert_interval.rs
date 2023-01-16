impl Solution {
    pub fn insert(intervals: Vec<Vec<i32>>, new_interval: Vec<i32>) -> Vec<Vec<i32>> {
        let new_interval_start = new_interval[0];
        let new_interval_end = new_interval[1];
        let mut state = 0;
        let mut interval_count = 0;
        let mut current_start = 0;
        let mut answer = vec![];
        for i in 0..intervals.len() {
            let interval = &intervals[i];
            for j in 0..2 {
                let event = if j == 0 { interval[0] } else { interval[1] };
                if state == 0 {
                    if new_interval_start <= event {
                        if interval_count == 0 {
                            current_start = new_interval_start;
                        }
                        interval_count = interval_count + 1;
                        state = 1;
                    }
                }
                if state == 1 {
                    if new_interval_end < event {
                        if interval_count == 1 {
                            let output_event = vec![current_start, new_interval_end];
                            answer.push(output_event);
                        }
                        interval_count = interval_count - 1;
                        state = 2;
                    }
                }

                if j == 0 {
                    if interval_count == 0 {
                        current_start = event;
                    }
                    interval_count = interval_count + 1;
                } else {
                    if interval_count == 1 {
                        let output_event = vec![current_start, event];
                        answer.push(output_event);
                    }
                    interval_count = interval_count - 1;
                }
            }
        }
        if state == 0 {
            let output_event = vec![new_interval_start, new_interval_end];
            answer.push(output_event);
        } else if state == 1 {
            let output_event = vec![current_start, new_interval_end];
            answer.push(output_event);
        }
        return answer;
    }
}

struct Solution {}

pub fn insert_interval() {
    let answers = Solution::insert(vec![vec![1, 3], vec![6, 9]], vec![2, 5]);
    for answer in answers {
        println!("{} {}", answer[0], answer[1]);
    }
}
