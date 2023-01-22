impl Solution {
    pub fn partition_helper(
        s: &[u8],
        prefix: &mut Vec<String>,
        i: usize,
        answers: &mut Vec<Vec<String>>,
    ) {
        if i == s.len() {
            answers.push(prefix.clone());
        } else {
            for j in (i + 1)..(s.len() + 1) {
                let mut palin = true;
                let mut l = i;
                let mut r = j;
                while l < r {
                    if s[l] != s[r - 1] {
                        palin = false;
                        break;
                    } else {
                        l = l + 1;
                        r = r - 1;
                    }
                }
                if palin {
                    prefix.push(String::from_utf8_lossy(&s[i..j]).to_string());
                    Self::partition_helper(s, prefix, j, answers);
                    prefix.pop();
                }
            }
        }
    }

    pub fn partition(s: String) -> Vec<Vec<String>> {
        let mut answers = vec![];
        let mut prefix = vec![];
        let b = s.as_bytes();
        Self::partition_helper(b, &mut prefix, 0, &mut answers);
        return answers;
    }
}

struct Solution {}

pub fn palindrome_partitioning() {
    let answers = Solution::partition("aab".to_string());
    for answer in answers {
        for element in answer {
            print!("{} ", element);
        }
        println!();
    }
}
