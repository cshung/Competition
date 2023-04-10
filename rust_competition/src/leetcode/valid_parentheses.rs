impl Solution {
    pub fn is_valid(t: String) -> bool {
        let mut s = vec![];
        let op = '(' as u8;
        let cp = ')' as u8;
        let ob = '{' as u8;
        let cb = '}' as u8;
        let os = '[' as u8;
        let cs = ']' as u8;
        for c in t.bytes() {
            if c == op {
                s.push(cp);
            } else if c == ob {
                s.push(cb);
            } else if c == os {
                s.push(cs);
            } else if c == cp {
                if let Some(sc) = s.pop() {
                    if sc != cp {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if c == cb {
                if let Some(sc) = s.pop() {
                    if sc != cb {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if c == cs {
                if let Some(sc) = s.pop() {
                    if sc != cs {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
        return s.len() == 0;
    }
}

struct Solution {}

pub fn valid_parentheses() {
    let answer = Solution::is_valid("()".to_string());
    println!("{}", answer);
}
