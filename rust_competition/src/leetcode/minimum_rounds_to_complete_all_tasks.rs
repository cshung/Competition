use std::collections::HashMap;

impl Solution {
    pub fn minimum_rounds(tasks: Vec<i32>) -> i32 {
        let mut counts = HashMap::new();
        for task in tasks {
            if let Some(count) = counts.get_mut(&task) {
                *count = *count + 1;
            } else {
                counts.insert(task, 1);
            }
        }
        let mut answer = 0;
        for (_task, c) in &counts {
            let count = *c;
            if count == 1 {
                return -1;
            } else if count % 3 == 0 {
                answer = answer + count / 3;
            } else if count % 3 == 1 {
                answer = answer + 2 + (count - 4) / 3;
            } else {
                answer = answer + 1 + (count - 2) / 3;
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn minimum_rounds_to_complete_all_tasks() {
    let answer = Solution::minimum_rounds(vec![2, 2, 3, 3, 2, 4, 4, 4, 4, 4]);
    println!("{}", answer);
}
