impl Solution {
    pub fn successful_pairs(spells: Vec<i32>, potions: Vec<i32>, success: i64) -> Vec<i32> {
        let mut sorted_potions = potions.clone();
        sorted_potions.sort();
        let mut answers = vec![];
        let m = sorted_potions.len();
        for spell in spells {
            let spell = spell as i64;
            let mut lo = 0;
            let mut hi = m;
            loop {
                let len = hi - lo;
                let mid = lo + len / 2;
                let mid_value = sorted_potions[mid] as i64;
                let test = spell * mid_value;
                if len == 1 {
                    if test >= success {
                        answers.push((m - lo) as i32);
                    } else {
                        answers.push((m - hi) as i32);
                    }
                    break;
                } else {
                    if test >= success {
                        hi = mid;
                    } else {
                        lo = mid;
                    }
                }
            }
        }
        return answers;
    }
}

struct Solution {}

pub fn successful_pairs_of_spells_and_potions() {
    let answers = Solution::successful_pairs(vec![5, 1, 3], vec![1, 2, 3, 4, 5], 7);
    for answer in answers {
        println!("{}", answer);
    }
}
