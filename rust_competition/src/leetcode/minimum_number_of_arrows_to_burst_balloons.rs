use std::cmp::Ordering;

struct Event {
    x: i32,
    enter: bool,
    index: usize,
}

impl Event {
    pub fn compare(left: &Event, right: &Event) -> Ordering {
        if left.x < right.x {
            return Ordering::Less;
        } else if (left.x == right.x) && left.enter && !right.enter {
            return Ordering::Less;
        } else {
            return Ordering::Greater;
        }
    }
}

impl Solution {
    pub fn find_min_arrow_shots(points: Vec<Vec<i32>>) -> i32 {
        let mut events: Vec<Event> = vec![];
        let mut bursted: Vec<bool> = vec![];
        for i in 0..points.len() {
            let point = &points[i];
            events.push(Event {
                x: point[0],
                enter: true,
                index: i,
            });
            events.push(Event {
                x: point[1],
                enter: false,
                index: i,
            });
            bursted.push(false);
        }
        events.sort_by(Event::compare);
        let mut seen = vec![];
        let mut count = 0;
        for event in events {
            if !bursted[event.index] {
                if event.enter {
                    seen.push(event.index);
                } else {
                    count = count + 1;
                    for s in &seen {
                        bursted[*s] = true;
                    }
                    seen.clear();
                }
            }
        }
        return count;
    }
}

struct Solution {}

pub fn minimum_number_of_arrows_to_burst_balloons() {
    let answer =
        Solution::find_min_arrow_shots(vec![vec![10, 16], vec![2, 8], vec![1, 6], vec![7, 12]]);
    println!("{}", answer);
}
