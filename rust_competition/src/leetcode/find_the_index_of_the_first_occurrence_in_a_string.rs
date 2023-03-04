impl Solution {
    pub fn str_str(haystack: String, needle: String) -> i32 {
        if let Some(result) = haystack.find(&needle) {
            return result as i32;
        } else {
            return -1;
        }
    }
}

struct Solution {}

pub fn find_the_index_of_the_first_occurrence_in_a_string() {
    let answer = Solution::str_str("Hello World".to_string(), "World".to_string());
    println!("{}", answer);
}
