use library::rand::Rand;

impl Solution {
    fn sort(nums: &mut Vec<i32>, start: usize, end: usize) {
        if end - start > 1 {
            let mut i = start;
            let mut j = start;
            let mut k = end - 1;
            let pivot = nums[start];
            while j <= k {
                if nums[j] < pivot {
                    let temp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = temp;
                    i = i + 1;
                    j = j + 1;
                } else if nums[j] == pivot {
                    j = j + 1;
                } else {
                    let temp = nums[k];
                    nums[k] = nums[j];
                    nums[j] = temp;
                    k = k - 1;
                }
            }
            Self::sort(nums, start, i);
            Self::sort(nums, k + 1, end);
        }
    }

    pub fn sort_array(nums: Vec<i32>) -> Vec<i32> {
        let n = nums.len();
        let mut answer = nums.clone();
        let mut rng = Rand::new(0);
        rng.shuffle(&mut answer);
        Self::sort(&mut answer, 0, n);
        return answer;
    }
}

struct Solution {}

pub fn sort_an_array() {
    let answer = Solution::sort_array(vec![5, 2, 3, 1]);
    for i in 0..answer.len() {
        print!("{} ", answer[i])
    }
}
