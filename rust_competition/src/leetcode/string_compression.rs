impl Solution {
    pub fn compress(chars: &mut Vec<char>) -> i32 {
        let n = chars.len();
        let mut read = 0;
        let mut write = 0;
        while read < n {
            let cur = chars[read];
            let mut count: usize = 0;
            while read < n {
                if chars[read] == cur {
                    count = count + 1;
                    read = read + 1;
                } else {
                    break;
                }
            }
            chars[write] = cur;
            write = write + 1;
            let mut b = false;
            if count > 999 {
                let t = (count / 1000) as u8;
                chars[write] = (t + '0' as u8) as char;
                write = write + 1;
                count = count - (t as usize) * 1000;
                b = true;
            }
            if b || count > 99 {
                let t = (count / 100) as u8;
                chars[write] = (t + '0' as u8) as char;
                write = write + 1;
                count = count - (t as usize) * 100;
                b = true;
            }
            if b || count > 9 {
                let t = (count / 10) as u8;
                chars[write] = (t + '0' as u8) as char;
                write = write + 1;
                count = count - (t as usize) * 10;
                b = true;
            }
            if b || count > 1 {
                chars[write] = ((count as u8) + '0' as u8) as char;
                write = write + 1;
            }
        }
        return write as i32;
    }
}

struct Solution {}

pub fn string_compression() {
    let mut input = vec!['a', 'a', 'b', 'b', 'c', 'c', 'c'];
    let answer = Solution::compress(&mut input) as usize;
    for i in 0..answer {
        print!("{}", input[i]);
    }
    println!();
}
