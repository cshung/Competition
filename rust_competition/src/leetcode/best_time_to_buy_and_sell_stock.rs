use std::cmp;

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let n = prices.len();
        let mut max_price = vec![0; n];
        for j in 0..n {
            let i = n - j - 1;
            if j == 0 {
                max_price[i] = prices[i];
            } else {
                max_price[i] = cmp::max(prices[i], max_price[i + 1]);
            }
        }
        let mut best = 0;
        for i in 0..(n - 1) {
            let profit = max_price[i + 1] - prices[i];
            if profit > best {
                best = profit;
            }
        }
        return best;
    }
}

struct Solution {}

pub fn best_time_to_buy_and_sell_stock() {
    let answer = Solution::max_profit(vec![7, 1, 5, 3, 6, 4]);
    println!("{}", answer);
}
