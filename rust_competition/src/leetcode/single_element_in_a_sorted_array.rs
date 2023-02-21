impl Solution {
    pub fn single_non_duplicate(nums: Vec<i32>) -> i32 {
        let mut lo = 0;
        let mut hi = nums.len();
        loop {
            if lo + 1 == hi {
                return nums[lo];
            }
            let mid = lo + (hi - lo) / 2;

            let even = ((mid + 1) % 2) == 0;
            let left = nums[mid - 1] == nums[mid];
            let right = nums[mid] == nums[mid + 1];

            let mut mode = 0;
            if even {
                mode = mode + 4;
            }
            if left {
                mode = mode + 2;
            }
            if right {
                mode = mode + 1;
            }
            let case = match mode {
                0 => 5,
                1 => 1,
                2 => 2,
                5 => 4,
                6 => 3,
                _ => panic!("Impossible"),
            };
            match case {
                1 => {
                    lo = mid;
                }
                2 => {
                    hi = mid + 1;
                }
                3 => {
                    lo = mid + 1;
                }
                4 => {
                    hi = mid;
                }
                5 => {
                    return nums[mid];
                }
                _ => panic!("Impossible"),
            };
        }
    }
}

struct Solution {}

pub fn single_element_in_a_sorted_array() {
    let answer = Solution::single_non_duplicate(vec![1, 1, 2, 3, 3, 4, 4, 8, 8]);
    println!("{}", answer);
}
