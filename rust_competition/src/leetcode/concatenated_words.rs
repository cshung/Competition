use std::collections::HashMap;
use std::convert::TryInto;

impl Solution {
    pub fn find_all_concatenated_words_in_a_dict(words: Vec<String>) -> Vec<String> {
        let mut hashs = HashMap::new();
        for word in &words {
            let bytes = word.as_bytes();
            let mut hash: i32 = 5381;
            for byteref in bytes {
                let byte: i32 = (*byteref).try_into().unwrap();
                hash = (hash << 5) + 1 + byte;
                if !hashs.contains_key(&hash) {
                    hashs.insert(hash, vec![]);
                }
            }
            hashs.get_mut(&hash).map(|f| {
                f.push(word.clone());
            });
        }
        let mut answers = vec![];
        for word in &words {
            let bytes = word.as_bytes();
            let n = word.len();
            let mut dp = vec![0; n + 1];
            dp[0] = 1;
            for i in 0..n {
                if dp[i] > 0 {
                    let mut hash = 5381;
                    for j in (i + 1)..(n + 1) {
                        let byte: i32 = (bytes[j - 1]).try_into().unwrap();
                        hash = (hash << 5) + 1 + byte;
                        if let Some(hits) = hashs.get_mut(&hash) {
                            for hit in hits {
                                if (*hit) == word[i..j] {
                                    dp[j] = dp[i] + 1;
                                }
                            }
                        } else {
                            break;
                        }
                    }
                }
            }
            if dp[n] > 2 {
                answers.push(word.clone());
            }
        }
        return answers;
    }
}

struct Solution {}

pub fn concatenated_words() {
    let answers = Solution::find_all_concatenated_words_in_a_dict(vec![
        "cat".to_string(),
        "cats".to_string(),
        "catsdogcats".to_string(),
        "dog".to_string(),
        "dogcatsdog".to_string(),
        "hippopotamuses".to_string(),
        "rat".to_string(),
        "ratcatdogcat".to_string(),
    ]);
    for answer in answers {
        println!("{}", answer);
    }
}
