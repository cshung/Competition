impl Solution {
    fn same(h1: &Vec<usize>, h2: &Vec<usize>) -> bool {
        for i in 0..26 {
            if h1[i] != h2[i] {
                return false;
            }
        }
        return true;
    }

    fn is_scramble_helper(
        memo: &mut Vec<Vec<Vec<Vec<Option<bool>>>>>,
        s1: &[usize],
        b1: usize,
        e1: usize,
        s2: &[usize],
        b2: usize,
        e2: usize,
    ) -> bool {
        if let Some(answer) = memo[b1][e1][b2][e2] {
            return answer;
        }
        let n = e1 - b1;
        if n < 4 {
            return true;
        }
        let mut head = vec![0; 26];
        let mut tail = vec![0; 26];
        let mut walk = vec![0; 26];
        for h in 0..(n - 1) {
            let h = h as usize;
            let t = n - h - 1;
            head[s1[h + b1]] += 1;
            tail[s1[t + b1]] += 1;
            walk[s2[h + b2]] += 1;
            if Self::same(&head, &walk) {
                if Self::is_scramble_helper(memo, s1, b1, b1 + h + 1, s2, b2, b2 + h + 1)
                    && Self::is_scramble_helper(memo, s1, b1 + h + 1, e1, s2, b2 + h + 1, e2)
                {
                    memo[b1][e1][b2][e2] = Some(true);
                    return true;
                }
            }
            if Self::same(&tail, &walk) {
                if Self::is_scramble_helper(memo, s1, b1, b1 + t, s2, b2 + h + 1, e2)
                    && Self::is_scramble_helper(memo, s1, b1 + t, e1, s2, b2, b2 + h + 1)
                {
                    memo[b1][e1][b2][e2] = Some(true);
                    return true;
                }
            }
        }
        memo[b1][e1][b2][e2] = Some(false);
        return false;
    }
    pub fn is_scramble(s1: String, s2: String) -> bool {
        let mut memo = vec![vec![vec![vec![None; 31]; 31]; 31]; 31];
        let mut u1 = vec![];
        let mut u2 = vec![];
        let a = 'a' as u8;
        for b1 in s1.as_bytes() {
            let c = (*b1) - a;
            u1.push(c as usize);
        }
        for b2 in s2.as_bytes() {
            let c = (*b2) - a;
            u2.push(c as usize);
        }
        let mut h1 = vec![0; 26];
        let mut h2 = vec![0; 26];
        for b1 in &u1 {
            h1[*b1] += 1;
        }
        for b2 in &u2 {
            h2[*b2] += 1;
        }
        for i in 0..25 {
            if h1[i] != h2[i] {
                return false;
            }
        }
        return Self::is_scramble_helper(&mut memo, &u1, 0, s1.len(), &u2, 0, s1.len());
    }
}

struct Solution {}

pub fn scramble_string() {
    let answer = Solution::is_scramble("great".to_string(), "rgeat".to_string());
    println!("{}", answer);
}
