impl Solution {
    fn dfs(
        parent: usize,
        current: usize,
        adjacency_lists: &Vec<Vec<usize>>,
        seats: i32,
    ) -> (i32, i64) {
        let mut size = 1;
        let mut cost = 0;
        for neighbor in &adjacency_lists[current] {
            if *neighbor != parent {
                let (neighbor_size, neighbor_cost) =
                    Self::dfs(current, *neighbor, adjacency_lists, seats);
                cost = cost + neighbor_cost;
                size = size + neighbor_size;
                cost = cost + (neighbor_size / seats) as i64;
                if (neighbor_size % seats) != 0 {
                    cost = cost + 1;
                }
            }
        }
        return (size, cost);
    }

    pub fn minimum_fuel_cost(roads: Vec<Vec<i32>>, seats: i32) -> i64 {
        let mut adjacency_lists = vec![];
        for road in roads {
            let src = road[0] as usize;
            let dst = road[1] as usize;
            while adjacency_lists.len() < src + 1 {
                adjacency_lists.push(vec![]);
            }
            while adjacency_lists.len() < dst + 1 {
                adjacency_lists.push(vec![]);
            }
            adjacency_lists[src].push(dst);
            adjacency_lists[dst].push(src);
        }

        let (_size, cost) = Self::dfs(adjacency_lists.len(), 0, &adjacency_lists, seats);
        return cost;
    }
}

struct Solution {}

pub fn minimum_fuel_cost_to_report_to_the_capital() {
    let answer = Solution::minimum_fuel_cost(
        vec![
            vec![3, 1],
            vec![3, 2],
            vec![1, 0],
            vec![0, 4],
            vec![0, 5],
            vec![4, 6],
        ],
        2,
    );
    println!("{}", answer);
}
