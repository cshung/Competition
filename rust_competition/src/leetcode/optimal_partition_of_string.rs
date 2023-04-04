impl Solution {
    pub fn partition_string(s: String) -> i32 {
        let s = s.as_bytes();
        let mut i = 0;
        let mut seen = vec![false; 26];
        let a = 'a' as u8;
        let mut answer = 0;
        while i < s.len() {
            let c = (s[i] - a) as usize;
            if seen[c] {
                for j in 0..26 {
                    seen[j] = false;
                }
                answer = answer + 1;
            }
            seen[c] = true;
            i = i + 1;
        }
        return answer + 1;
    }
}

struct Solution {}

pub fn optimal_partition_of_string() {
    let answer = Solution::partition_string("abacaba".to_string());
    println!("{}", answer);
}
