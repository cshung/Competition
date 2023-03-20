impl Solution {
    pub fn can_place_flowers(flowerbed: Vec<i32>, n: i32) -> bool {
        let mut count = 0;
        let mut placing = vec![0];
        for i in 0..flowerbed.len() {
            placing.push(flowerbed[i]);
        }
        placing.push(0);
        for j in 0..flowerbed.len() {
            let i = j + 1;
            if placing[i - 1] == 0 && placing[i] == 0 && placing[i + 1] == 0 {
                placing[i] = 1;
                count = count + 1;
            }
        }
        return count >= n;
    }
}

struct Solution {}

pub fn can_place_flowers() {
    let answer = Solution::can_place_flowers(vec![1, 0, 0, 0, 1], 1);
    println!("{}", answer);
}
