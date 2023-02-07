use std::cmp;

impl Solution {
    pub fn total_fruit(fruits: Vec<i32>) -> i32 {
        let mut basket1 = None;
        let mut basket2 = None;
        let mut last1 = None;
        let mut last2 = None;
        let mut start = 0;
        let mut answer = 0;

        for i in 0..fruits.len() {
            let fruit = fruits[i];
            if basket1 == Some(fruit) {
                last1 = Some(i);
            } else if basket2 == Some(fruit) {
                last2 = Some(i);
            } else if basket1 == None {
                basket1 = Some(fruit);
                last1 = Some(i);
            } else if basket2 == None {
                basket2 = Some(fruit);
                last2 = Some(i);
            } else {
                if Some(fruits[i - 1]) == basket1 {
                    start = last2.unwrap() + 1;
                    basket2 = Some(fruit);
                    last2 = Some(i);
                } else {
                    start = last1.unwrap() + 1;
                    basket1 = Some(fruit);
                    last1 = Some(i);
                }
            }
            answer = cmp::max(answer, (i - start + 1) as i32);
        }

        return answer;
    }
}

struct Solution {}

pub fn fruit_into_baskets() {
    let answer = Solution::total_fruit(vec![1, 2, 1]);
    println!("{}", answer);
}
