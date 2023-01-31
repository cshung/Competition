impl Solution {
    pub fn detect_capital_use(word: String) -> bool {
        let bytes = word.as_bytes();
        let cap_a = 'A' as u8;
        let cap_z = 'Z' as u8;
        let mut state = 0;

        // state = 0 means ""
        // state = 1 means C
        // state = 2 means c+
        // state = 3 means CC+
        // state = 4 means Cc+

        for rb in bytes {
            let b = *rb;
            let caps = cap_a <= b && b <= cap_z;
            if state == 0 {
                if caps {
                    state = 1;
                } else {
                    state = 2;
                }
            } else if state == 1 {
                if caps {
                    state = 3;
                } else {
                    state = 4;
                }
            } else if state == 2 {
                if caps {
                    return false;
                }
            } else if state == 3 {
                if !caps {
                    return false;
                }
            } else if state == 4 {
                if caps {
                    return false;
                }
            }
        }
        return true;
    }
}

struct Solution {}

pub fn detect_capital() {
    let answer = Solution::detect_capital_use("USA".to_string());
    println!("{}", answer);
}
