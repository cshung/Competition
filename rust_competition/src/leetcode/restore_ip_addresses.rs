impl Solution {
    fn find_ip_addresses(
        s: &[u8],
        numbers: &mut Vec<i32>,
        current: i32,
        index: usize,
        count: usize,
        answers: &mut Vec<String>,
    ) {
        if index == s.len() {
            if count == 3 {
                numbers[count] = current;
                answers.push(format!(
                    "{}.{}.{}.{}",
                    numbers[0], numbers[1], numbers[2], numbers[3]
                ));
            } else {
                return;
            }
        } else if count > 3 {
            return;
        } else {
            let p: i32 = (s[index] - ('0' as u8)).into();
            if current == -1 {
                Self::find_ip_addresses(s, numbers, p, index + 1, count, answers);
            } else if current == 0 {
                numbers[count] = 0;
                Self::find_ip_addresses(s, numbers, -1, index, count + 1, answers);
            } else {
                numbers[count] = current;
                Self::find_ip_addresses(s, numbers, -1, index, count + 1, answers);
                let next: i32 = current * 10 + p;
                if next > 255 {
                    return;
                } else {
                    Self::find_ip_addresses(s, numbers, next, index + 1, count, answers);
                }
            }
        }
    }

    pub fn restore_ip_addresses(s: String) -> Vec<String> {
        let b = s.as_bytes();
        let mut answers = vec![];
        let mut numbers = vec![0, 0, 0, 0];
        Self::find_ip_addresses(&b, &mut numbers, -1, 0, 0, &mut answers);
        return answers;
    }
}

struct Solution {}

pub fn restore_ip_addresses() {
    let answers = Solution::restore_ip_addresses("25525511135".to_string());
    for answer in answers {
        println!("{}", answer);
    }
}
