use library::min_max_heap::MinMaxHeap;
use std::cmp::Ordering;

struct Project {
    profit: i32,
    capital: i32,
}

impl Project {
    pub fn compare(left: &Project, right: &Project) -> Ordering {
        if left.capital < right.capital {
            return Ordering::Less;
        } else {
            return Ordering::Greater;
        }
    }
}

impl Solution {
    pub fn find_maximized_capital(k: i32, w: i32, profits: Vec<i32>, capital: Vec<i32>) -> i32 {
        let k = k as usize;
        let mut projects = vec![];
        for i in 0..profits.len() {
            projects.push(Project {
                profit: profits[i],
                capital: capital[i],
            });
        }
        projects.sort_by(Project::compare);
        let mut queue = MinMaxHeap::new(k as usize);
        let mut p = 0;
        let mut current_capital = w;

        for _ in 0..k {
            while p < projects.len() {
                if projects[p].capital <= current_capital {
                    if queue.get_size() == k {
                        let mut unused = 0;
                        queue.try_delete_min(&mut unused);
                    }
                    queue.try_insert(projects[p].profit);
                    p += 1;
                } else {
                    break;
                }
            }
            let mut best = 0;
            if queue.try_delete_max(&mut best) {
                current_capital += best;
            } else {
                break;
            }
        }
        return current_capital;
    }
}

struct Solution {}

pub fn ipo() {
    let answer = Solution::find_maximized_capital(2, 0, vec![1, 2, 3], vec![0, 1, 1]);
    println!("{}", answer);
}
