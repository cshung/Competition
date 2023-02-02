impl Solution {
    pub fn is_alien_sorted(words: Vec<String>, order: String) -> bool {
        let order_bytes = order.as_bytes();
        let mut inverse: Vec<u8> = vec![0; 26];
        let a = 'a' as u8;
        for i in 0..26 {
            inverse[(order_bytes[i] - a) as usize] = a + (i as u8);
        }
        let mut last_word = None;
        for word in words {
            let translated: String = word
                .chars()
                .map(|x| inverse[(x as u8 - a) as usize] as char)
                .collect();
            if let Some(last_word) = last_word {
                if translated < last_word {
                    return false;
                }
            }
            last_word = Some(translated);
        }
        return true;
    }
}

struct Solution {}

pub fn verifying_an_alien_dictionary() {
    let answer = Solution::is_alien_sorted(
        vec!["hello".to_string(), "leetcode".to_string()],
        "hlabcdefgijkmnopqrstuvwxyz".to_string(),
    );
    println!("{}", answer);
}
