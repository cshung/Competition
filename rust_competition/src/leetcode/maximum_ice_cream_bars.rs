impl Solution {
    pub fn max_ice_cream(costs: Vec<i32>, coins: i32) -> i32 {
        let mut c = costs.clone();
        c.sort();
        let mut spent = 0;
        let mut count = 0;
        for cost in c {
            if (spent + cost)  <= coins
            {
                count = count + 1;
                spent = spent + cost;
            }
            else
            {
                break;
            }
        }
        return count;
    }
}

struct Solution
{
}

pub fn maximum_ice_cream_bars()
{
    let answer = Solution::max_ice_cream(vec![1,3,2,4,1], 7);
    println!("{}", answer);
}