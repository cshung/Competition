impl Solution {
    pub fn convert(s: String, num_rows: i32) -> String {
        if num_rows == 1 {
            return s;
        }
        let nr = num_rows as usize;
        let n = s.len();
        let bytes = s.as_bytes();
        let mut buffer = vec![vec![None; n]; nr];
        let mut r = 0;
        let mut c = 0;
        let mut down = true;
        for i in 0..n {
            buffer[r][c] = Some(bytes[i]);
            if down {
                r = r + 1;
                if r == nr {
                    c = c + 1;
                    r = nr - 2;
                    down = false;
                }
            } else {
                if r == 0 {
                    down = true;
                    r = 1;
                } else {
                    r = r - 1;
                    c = c + 1
                }
            }
        }
        let mut answer = "".to_string();
        {
            for pr in 0..nr {
                for pc in 0..n {
                    if let Some(b) = buffer[pr][pc] {
                        answer.push(b as char);
                    }
                }
            }
        }
        return answer;
    }
}

struct Solution {}

pub fn zigzag_conversion() {
    let answer = Solution::convert("PAYPALISHIRING".to_string(), 3);
    println!("{}", answer);
}
