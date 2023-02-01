pub fn gcd(a: usize, b: usize) -> usize {
    let mut _a = a;
    let mut _b = b;
    while _b != 0 {
        let tmp = _a;
        _a = _b;
        _b = tmp % _b;
    }
    _a
}

impl Solution {
    pub fn gcd_of_strings(str1: String, str2: String) -> String {
        let b1 = str1.as_bytes();
        let b2 = str2.as_bytes();
        let m = b1.len();
        let n = b2.len();
        let g = gcd(m, n);
        println!("{}", g);
        let candidate = &str1[0..g];
        for i in 0..(m / g) {
            let begin = i * g;
            let end = begin + g;
            if &str1[begin..end] != candidate {
                return "".to_string();
            }
        }
        for i in 0..(n / g) {
            let begin = i * g;
            let end = begin + g;
            if &str2[begin..end] != candidate {
                return "".to_string();
            }
        }

        return candidate.to_string();
    }
}

struct Solution {}

pub fn greatest_common_divisor_of_strings() {
    let answer = Solution::gcd_of_strings("ABCABC".to_string(), "ABC".to_string());
    println!("{}", answer);
}
