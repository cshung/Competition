use std::convert::TryInto;

impl Solution {
    pub fn find_cheapest_price(n: i32, flights: Vec<Vec<i32>>, src: i32, dst: i32, k: i32) -> i32 {
        let sn: usize = n.try_into().unwrap();
        let s_src: usize = src.try_into().unwrap();
        let s_dst: usize = dst.try_into().unwrap();
        let num_flights: usize = (k + 1).try_into().unwrap();
        let mut buffer1 = vec![];
        let mut buffer2 = vec![];
        for i in 0..sn {
            if i == s_src {
                buffer1.push(Some(0));
            } else {
                buffer1.push(None);
            }
            buffer2.push(Some(0));
        }

        let mut current = &mut buffer1;
        let mut next = &mut buffer2;
        for _f in 0..num_flights {
            for i in 0..sn {
                next[i] = current[i];
            }
            for e in 0..flights.len() {
                let flight_src: usize = flights[e][0].try_into().unwrap();
                let flight_dst: usize = flights[e][1].try_into().unwrap();
                let flight_cost = flights[e][2];
                let maybe_src_cost = current[flight_src];
                if let Some(src_cost) = maybe_src_cost {
                    let fly_cost = src_cost + flight_cost;
                    if let Some(cur_cost) = next[flight_dst] {
                        if fly_cost < cur_cost {
                            next[flight_dst] = Some(fly_cost);
                        }
                    } else {
                        next[flight_dst] = Some(fly_cost);
                    }
                }
            }

            let temp = current;
            current = next;
            next = temp;
        }

        if let Some(opt_cost) = current[s_dst] {
            return opt_cost;
        } else {
            return -1;
        }
    }
}

struct Solution {}

pub fn cheapest_flights_within_k_stops() {
    let answer = Solution::find_cheapest_price(
        4,
        vec![
            vec![0, 1, 100],
            vec![1, 2, 100],
            vec![2, 0, 100],
            vec![1, 3, 600],
            vec![2, 3, 200],
        ],
        0,
        3,
        1,
    );
    println!("{}", answer);
}
