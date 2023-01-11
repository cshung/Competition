use std::convert::TryInto;

impl Solution {
    fn cost(
        parent: usize,
        current: usize,
        adj_list: &Vec<Vec<usize>>,
        has_apple: &Vec<bool>,
    ) -> i32 {
        let mut answer = 0;
        for neighbor in &adj_list[current] {
            if *neighbor != parent {
                answer = answer + Self::cost(current, *neighbor, adj_list, has_apple);
            }
        }
        if (answer != 0) || has_apple[current] {
            answer = answer + 2;
        }
        return answer;
    }

    pub fn min_time(n: i32, edges: Vec<Vec<i32>>, has_apple: Vec<bool>) -> i32 {
        let mut adj_list = vec![];
        for _ in 0..n {
            adj_list.push(vec![]);
        }
        for edge in edges {
            let from: usize = edge[0].try_into().unwrap();
            let to: usize = edge[1].try_into().unwrap();
            adj_list[from].push(to);
            adj_list[to].push(from);
        }
        let result = Self::cost(n.try_into().unwrap(), 0, &adj_list, &has_apple);
        if result > 0 {
            return result - 2;
        } else {
            return 0;
        }
    }
}

struct Solution {}

pub fn minimum_time_to_collect_all_apples_in_a_tree() {
    let answer = Solution::min_time(
        7,
        vec![
            vec![0, 1],
            vec![0, 2],
            vec![1, 4],
            vec![1, 5],
            vec![2, 3],
            vec![2, 6],
        ],
        vec![false, false, true, false, true, true, false],
    );
    println!("{}", answer);
}
