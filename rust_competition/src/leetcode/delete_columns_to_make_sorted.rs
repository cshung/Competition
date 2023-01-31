impl Solution {
    pub fn min_deletion_size(strs: Vec<String>) -> i32 {
        let n = strs.len();
        if n == 0 {
            return 0;
        }
        let w = strs[0].len();
        let mut answer = 0;
        let mut deleted = vec![false; w];
        for r in 0..(n - 1) {
            let current = strs[r].as_bytes();
            let next = strs[r + 1].as_bytes();
            for c in 0..w {
                if !deleted[c] {
                    if current[c] > next[c] {
                        deleted[c] = true;
                        answer = answer + 1;
                    }
                }
            }
        }

        return answer;
    }
}

struct Solution {}

pub fn delete_columns_to_make_sorted() {
    let answer = Solution::min_deletion_size(vec![
        "cba".to_string(),
        "daf".to_string(),
        "ghi".to_string(),
    ]);
    println!("{}", answer);
}
