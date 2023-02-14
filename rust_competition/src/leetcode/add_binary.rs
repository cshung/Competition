impl Solution {
    pub fn add_binary(a: String, b: String) -> String {
        let a: Vec<char> = a.chars().collect();
        let b: Vec<char> = b.chars().collect();
        let mut r: Vec<char> = vec![];
        let mut c = 0;
        let mut i = 0;
        loop {
            let ac = if i < a.len() { a[a.len() - i - 1] } else { '0' };
            let bc = if i < b.len() { b[b.len() - i - 1] } else { '0' };
            let ad = (ac as u8) - ('0' as u8);
            let bd = (bc as u8) - ('0' as u8);
            let s = ad + bd + c;
            let rd = if s > 1 { s - 2 } else { s };
            let rc = (rd + ('0' as u8)) as char;
            c = if s > 1 { 1 } else { 0 };
            i = i + 1;
            r.push(rc);
            if (i >= a.len()) && (i >= b.len()) && (c == 0) {
                break;
            }
        }
        r.reverse();
        return r.iter().collect();
    }
}

struct Solution {}

pub fn add_binary() {
    let answer = Solution::add_binary("1111".to_string(), "1111".to_string());
    println!("{}", answer);
}
