use std::cmp;
use std::collections::HashMap;
use std::collections::VecDeque;
use std::convert::TryInto;

impl Solution {
    pub fn snakes_and_ladders(board: Vec<Vec<i32>>) -> i32 {
        let height = board.len();
        let width = board[0].len();
        let size = height * width;
        let mut r: usize = height;
        let mut c: usize = 1;
        let mut d: i32 = 1;
        let mut map: HashMap<usize, usize> = HashMap::new();
        let mut adjacency_list: Vec<Vec<usize>> = vec![vec![]; size];
        for i in 0..size {
            let cell = board[r - 1][c - 1];
            if cell != -1 {
                map.insert(i, (cell - 1).try_into().unwrap());
            }
            let ic: i32 = c.try_into().unwrap();
            c = (ic + d).try_into().unwrap();
            if c == 0 {
                c = 1;
                r = r - 1;
                d = d * -1;
            } else if c == width + 1 {
                c = width;
                r = r - 1;
                d = d * -1;
            }
        }

        for i in 0..size {
            for j in i..cmp::min(i + 6, size - 1) {
                let mut k = j + 1;
                if let Some(nk) = map.get(&k) {
                    k = *nk;
                }
                adjacency_list[i].push(k);
            }
        }

        let mut bfs: VecDeque<usize> = VecDeque::from([0]);
        let mut dists = vec![-1; size];
        dists[0] = 0;
        while bfs.len() > 0 {
            let cur = bfs.pop_front().unwrap();
            for rn in &adjacency_list[cur] {
                let n = *rn;
                if dists[n] == -1 {
                    dists[n] = dists[cur] + 1;
                    if n == size - 1 {
                        return dists[n];
                    } else {
                        bfs.push_back(n);
                    }
                }
            }
        }

        return -1;
    }
}

struct Solution {}

pub fn snakes_and_ladders() {
    let answer = Solution::snakes_and_ladders(vec![
        vec![-1, -1, -1, -1, -1, -1],
        vec![-1, -1, -1, -1, -1, -1],
        vec![-1, -1, -1, -1, -1, -1],
        vec![-1, 35, -1, -1, 13, -1],
        vec![-1, -1, -1, -1, -1, -1],
        vec![-1, 15, -1, -1, -1, -1],
    ]);
    println!("{}", answer);
}
