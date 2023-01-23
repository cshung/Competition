use std::convert::TryInto;

impl Solution {
    pub fn find_judge(n: i32, trust: Vec<Vec<i32>>) -> i32 {
        let ns = n.try_into().unwrap();
        let mut trust_counts = vec![0; ns];
        let mut be_trust_counts = vec![0; ns];
        for edge in trust {
            let src: usize = (edge[0] - 1).try_into().unwrap();
            let dst: usize = (edge[1] - 1).try_into().unwrap();
            trust_counts[src] = trust_counts[src] + 1;
            be_trust_counts[dst] = be_trust_counts[dst] + 1;
        }
        for i in 0..ns {
            if (trust_counts[i] == 0) && (be_trust_counts[i] == n - 1) {
                return (i + 1).try_into().unwrap();
            }
        }
        return -1;
    }
}

struct Solution {}

pub fn find_the_town_judge() {
    let answer = Solution::find_judge(2, vec![vec![1, 2]]);
    println!("{}", answer);
}
