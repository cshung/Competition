use std::cmp;
use std::convert::TryInto;

impl Solution {
    fn find_set(c: i16, s: &mut Vec<i16>) -> i16 {
        let uc: usize = c.try_into().unwrap();
        if s[uc] < 0 {
            return c;
        } else {
            s[uc] = Self::find_set(s[uc], s);
            return s[uc];
        }
    }

    fn union_set(c1: i16, c2: i16, s: &mut Vec<i16>, m: &mut Vec<usize>) {
        let d1 = Self::find_set(c1, s);
        let d2 = Self::find_set(c2, s);
        if d1 != d2 {
            let ud1: usize = d1.try_into().unwrap();
            let ud2: usize = d2.try_into().unwrap();
            let m1 = m[ud1];
            let m2 = m[ud2];
            let min = cmp::min(m1, m2);
            let size1 = -s[ud1];
            let size2 = -s[ud2];
            let total = size1 + size2;
            if size1 > size2 {
                s[ud2] = d1;
                s[ud1] = -total;
                m[ud1] = min;
            } else {
                s[ud1] = d2;
                s[ud2] = -total;
                m[ud2] = min;
            }
        }
    }

    pub fn smallest_equivalent_string(s1: String, s2: String, base_str: String) -> String {
        let b1 = s1.as_bytes();
        let b2 = s2.as_bytes();
        let bb = base_str.as_bytes();
        let n = b1.len();
        let mut s = vec![-1; 26];
        let mut m = vec![0; 26];
        for i in 0..26 {
            m[i] = i;
        }
        for i in 0..n {
            let c1 = b1[i] as i16 - ('a' as i16);
            let c2 = b2[i] as i16 - ('a' as i16);
            Self::union_set(c1, c2, &mut s, &mut m);
        }
        let mut buffer = vec![];
        for i in 0..(base_str.len()) {
            let c: i16 = bb[i] as i16 - ('a' as i16);
            let d: i16 = Self::find_set(c, &mut s);
            let e: usize = d.try_into().unwrap();
            let f: usize = m[e];
            let g: u8 = f.try_into().unwrap();
            let h: u8 = g + ('a' as u8);
            buffer.push(h);
        }
        return String::from_utf8(buffer).unwrap();
    }
}

struct Solution {}

pub fn lexicographically_smallest_equivalent_string() {
    let answer = Solution::smallest_equivalent_string(
        "parker".to_string(),
        "morris".to_string(),
        "parser".to_string(),
    );
    println!("{}", answer);
}
