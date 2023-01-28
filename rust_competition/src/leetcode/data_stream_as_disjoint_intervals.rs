use std::collections::BTreeSet;
use std::convert::TryInto;

struct SummaryRanges {
    starts: BTreeSet<i32>,
    ends: BTreeSet<i32>,
    hot: Vec<bool>,
}

impl SummaryRanges {
    fn new() -> Self {
        return SummaryRanges {
            starts: BTreeSet::new(),
            ends: BTreeSet::new(),
            hot: vec![false; 10001],
        };
    }

    fn add_num(&mut self, value: i32) {
        let value_usize: usize = value.try_into().unwrap();
        if !self.hot[value_usize] {
            self.hot[value_usize] = true;
            if value > 0 {
                let previous = value - 1;
                let previous_usize: usize = previous.try_into().unwrap();
                if self.hot[previous_usize] {
                    self.ends.remove(&previous);
                } else {
                    self.starts.insert(value);
                }
            } else {
                self.starts.insert(0);
            }
            if value < 10000 {
                let next = value + 1;
                let next_usize: usize = next.try_into().unwrap();
                if self.hot[next_usize] {
                    self.starts.remove(&next);
                } else {
                    self.ends.insert(value);
                }
            }
        }
    }

    fn get_intervals(&self) -> Vec<Vec<i32>> {
        let mut first = vec![];
        let mut second = vec![];
        for s in &self.starts {
            first.push(*s);
        }
        for e in &self.ends {
            second.push(*e);
        }
        let mut answers = vec![];
        for i in 0..first.len() {
            let f = first[i];
            let s = second[i];
            let interval = vec![f, s];
            answers.push(interval);
        }
        return answers;
    }
}

pub fn data_stream_as_disjoint_intervals() {
    let mut obj = SummaryRanges::new();
    obj.add_num(1);
    {
        let intervals: Vec<Vec<i32>> = obj.get_intervals();
        for interval in intervals {
            print!("[{}, {}],", interval[0], interval[1]);
        }
        println!();
    }
    obj.add_num(3);
    {
        let intervals: Vec<Vec<i32>> = obj.get_intervals();
        for interval in intervals {
            print!("[{}, {}],", interval[0], interval[1]);
        }
        println!();
    }
    obj.add_num(7);
    {
        let intervals: Vec<Vec<i32>> = obj.get_intervals();
        for interval in intervals {
            print!("[{}, {}],", interval[0], interval[1]);
        }
        println!();
    }
    obj.add_num(2);
    {
        let intervals: Vec<Vec<i32>> = obj.get_intervals();
        for interval in intervals {
            print!("[{}, {}],", interval[0], interval[1]);
        }
        println!();
    }
    obj.add_num(6);
    {
        let intervals: Vec<Vec<i32>> = obj.get_intervals();
        for interval in intervals {
            print!("[{}, {}],", interval[0], interval[1]);
        }
        println!();
    }
}
