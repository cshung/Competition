use std::collections::HashMap;
use std::convert::TryInto;

impl Solution {
    fn count_sub_trees_helper(
        parent: usize,
        current: usize,
        adj_list: &Vec<Vec<usize>>,
        numbers: &Vec<usize>,
        counts: &mut Vec<i32>,
        answer: &mut Vec<i32>,
    ) {
        let number = numbers[current];
        let before = counts[number];
        counts[number] = counts[number] + 1;
        for neighbor in &adj_list[current] {
            if *neighbor != parent {
                Self::count_sub_trees_helper(current, *neighbor, adj_list, numbers, counts, answer);
            }
        }
        answer[current] = counts[number] - before;
    }

    pub fn count_sub_trees(n: i32, edges: Vec<Vec<i32>>, labels: String) -> Vec<i32> {
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
        let mut numbers = vec![];
        let mut map = HashMap::new();
        for c in labels.chars() {
            if let Some(number) = map.get(&c) {
                numbers.push(*number);
            } else {
                let number = map.len();
                numbers.push(number);
                map.insert(c, number);
            }
        }

        let mut counts = vec![0; map.len()];
        let mut answer = vec![0; n.try_into().unwrap()];
        Self::count_sub_trees_helper(
            n.try_into().unwrap(),
            0,
            &adj_list,
            &numbers,
            &mut counts,
            &mut answer,
        );
        return answer;
    }
}

struct Solution {}

pub fn number_of_nodes_in_the_sub_tree_with_the_same_label() {
    let answers = Solution::count_sub_trees(
        7,
        vec![
            vec![0, 1],
            vec![0, 2],
            vec![1, 4],
            vec![1, 5],
            vec![2, 3],
            vec![2, 6],
        ],
        "abaedcd".to_string(),
    );
    for answer in answers {
        println!("{}", answer);
    }
}
