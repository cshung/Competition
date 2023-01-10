use std::collections::HashMap;

pub fn gcd(a: i32, b: i32) -> i32 {
    let mut _a = a;
    let mut _b = b;
    while _b != 0 {
        let tmp = _a;
        _a = _b;
        _b = tmp % _b;
    }
    _a
}

#[derive(PartialEq, Eq, Hash)]
struct Line {
    a: i32,
    b: i32,
    c: i32,
}

impl Solution {
    pub fn max_points(points: Vec<Vec<i32>>) -> i32 {
        let n = points.len();
        if n == 1 {
            return 1;
        }
        let mut lines = HashMap::new();
        for i in 0..n {
            for j in (i + 1)..n {
                let x1 = points[i][0];
                let y1 = points[i][1];
                let x2 = points[j][0];
                let y2 = points[j][1];
                let mut a = y1 - y2;
                let mut b = x2 - x1;
                let mut c = (x1 - x2) * y1 + (y2 - y1) * x1;
                let g = gcd(gcd(a, b), c);
                a = a / g;
                b = b / g;
                c = c / g;

                if (a < 0) || ((a == 0) && (b < 0)) {
                    a = a * -1;
                    b = b * -1;
                    c = c * -1;
                }

                lines.insert(Line { a: a, b: b, c: c }, 0);
            }
        }
        let mut max = 0;
        for (line, _c) in &lines {
            let a = line.a;
            let b = line.b;
            let c = line.c;
            let mut count = 0;
            for i in 0..n {
                let x1 = points[i][0];
                let y1 = points[i][1];
                let v = a * x1 + b * y1 + c;
                if v == 0 {
                    count = count + 1;
                }
            }
            if count > max {
                max = count;
            }
        }
        return max;
    }
}

struct Solution {}

pub fn max_points_on_a_line() {
    let answer = Solution::max_points(vec![vec![1, 1], vec![2, 2], vec![3, 3]]);
    println!("{}", answer);
}
