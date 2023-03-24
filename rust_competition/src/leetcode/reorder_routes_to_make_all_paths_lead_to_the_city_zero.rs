impl Solution {
    fn dfs(
        parent: usize,
        current: usize,
        parents: &mut Vec<usize>,
        adjacency_lists: &Vec<Vec<usize>>,
    ) {
        parents[current] = parent;
        for neighbor in &adjacency_lists[current] {
            if *neighbor != parent {
                Self::dfs(current, *neighbor, parents, adjacency_lists);
            }
        }
    }

    pub fn min_reorder(n: i32, connections: Vec<Vec<i32>>) -> i32 {
        let n = n as usize;
        let mut adjacency_lists = vec![vec![]; n];
        for connection in &connections {
            let src = connection[0] as usize;
            let dst = connection[1] as usize;
            adjacency_lists[src].push(dst);
            adjacency_lists[dst].push(src);
        }
        let mut parents = vec![0; n];
        Self::dfs(n, 0, &mut parents, &adjacency_lists);
        let mut flip = 0;
        for connection in &connections {
            let src = connection[0] as usize;
            let dst = connection[1] as usize;
            if parents[src] != dst {
                flip += 1;
            }
        }
        return flip;
    }
}

struct Solution {}

pub fn reorder_routes_to_make_all_paths_lead_to_the_city_zero() {
    let answer = Solution::min_reorder(
        6,
        vec![vec![0, 1], vec![1, 3], vec![2, 3], vec![4, 0], vec![4, 5]],
    );
    println!("{}", answer);
}
