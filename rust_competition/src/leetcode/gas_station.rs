use std::convert::TryInto;

impl Solution {
    pub fn can_complete_circuit(gas: Vec<i32>, cost: Vec<i32>) -> i32 {
        let mut balance = 0;
        let mut min_balance = -1;
        let mut min_balance_index : i32 = -1;
        let n = gas.len();
        let n_i32 : i32 = n.try_into().unwrap();
        for i in 0..n
        {
            balance = balance + (gas[i] - cost[i]);
            if (min_balance_index == -1) || (balance < min_balance)
            {
                min_balance = balance;
                min_balance_index = i.try_into().unwrap();
            }
        }
        if balance >= 0
        {
            return (min_balance_index + 1) % n_i32;
        }
        else
        {
            return -1;
        }
    }
}

struct Solution
{
}

pub fn gas_station()
{
    let answer = Solution::can_complete_circuit(vec![1,2,3,4,5], vec![3,4,5,1,2]);
    println!("{}", answer);
}