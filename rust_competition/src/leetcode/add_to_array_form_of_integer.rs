impl Solution {
    pub fn add_to_array_form(num: Vec<i32>, k: i32) -> Vec<i32> {
        let mut result = vec![];
        let mut c = 0;
        let mut r = k;
        let mut i = 0;
        loop {
            let a = if i < num.len() {
                num[num.len() - i - 1]
            } else {
                0
            };
            let b = r % 10;
            let mut s = a + b + c;
            if s > 9 {
                s = s - 10;
                c = 1;
            } else {
                c = 0;
            }
            result.push(s);
            r = r / 10;
            if (r == 0) && (c == 0) && (i >= num.len() - 1) {
                break;
            }
            i = i + 1;
        }
        result.reverse();
        return result;
    }
}

struct Solution {}

pub fn add_to_array_form_of_integer() {
    let answers = Solution::add_to_array_form(vec![1, 2, 0, 0], 34);
    for answer in answers {
        print!("{}", answer);
    }
    println!();
}
