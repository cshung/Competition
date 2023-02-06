impl Solution {
    pub fn shuffle(nums: Vec<i32>, n: i32) -> Vec<i32> {
        let n = n as usize;
        let mut answers = vec![];
        for i in 0..n {
            answers.push(nums[i]);
            answers.push(nums[n + i]);
        }
        return answers;
    }
}

struct Solution {}

pub fn shuffle_the_array() {
    let answers = Solution::shuffle(vec![2, 5, 1, 3, 4, 7], 3);
    for answer in answers {
        print!("{} ", answer);
    }
    println!();
}
