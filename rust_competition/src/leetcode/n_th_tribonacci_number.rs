impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        match n {
            0 => 0,
            1 => 1,
            2 => 1,
            3 => 2,
            4 => 4,
            5 => 7,
            6 => 13,
            7 => 24,
            8 => 44,
            9 => 81,
            10 => 149,
            11 => 274,
            12 => 504,
            13 => 927,
            14 => 1705,
            15 => 3136,
            16 => 5768,
            17 => 10609,
            18 => 19513,
            19 => 35890,
            20 => 66012,
            21 => 121415,
            22 => 223317,
            23 => 410744,
            24 => 755476,
            25 => 1389537,
            26 => 2555757,
            27 => 4700770,
            28 => 8646064,
            29 => 15902591,
            30 => 29249425,
            31 => 53798080,
            32 => 98950096,
            33 => 181997601,
            34 => 334745777,
            35 => 615693474,
            36 => 1132436852,
            37 => 2082876103,
            _ => -1,
        }
    }
}

struct Solution {}

pub fn n_th_tribonacci_number() {
    let answer = Solution::tribonacci(25);
    println!("{}", answer);
}
