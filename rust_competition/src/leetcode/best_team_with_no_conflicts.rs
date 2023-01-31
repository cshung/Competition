use std::cmp;
use std::cmp::Ordering;

struct Player {
    score: i32,
    age: i32,
}

impl Player {
    pub fn compare(left: &Player, right: &Player) -> Ordering {
        if left.age < right.age {
            return Ordering::Less;
        } else if left.age > right.age {
            return Ordering::Greater;
        } else if left.score < right.score {
            return Ordering::Less;
        } else if left.score > right.score {
            return Ordering::Greater;
        } else {
            return Ordering::Equal;
        }
    }

    pub fn conflict(left: &Player, right: &Player) -> bool {
        if left.age < right.age {
            if left.score > right.score {
                return true;
            }
        }
        return false;
    }
}

impl Solution {
    pub fn best_team_score(scores: Vec<i32>, ages: Vec<i32>) -> i32 {
        let n = scores.len();
        let mut players = vec![];
        for i in 0..n {
            let player = Player {
                score: scores[i],
                age: ages[i],
            };
            players.push(player);
        }
        players.sort_by(Player::compare);
        let mut lis = vec![1; n];
        lis[0] = players[0].score;
        let mut best = lis[0];
        for i in 1..n {
            lis[i] = players[i].score;
            for j in 0..i {
                if !Player::conflict(&players[j], &players[i]) {
                    lis[i] = cmp::max(lis[i], players[i].score + lis[j]);
                }
            }
            best = cmp::max(best, lis[i]);
        }
        return best;
    }
}

struct Solution {}

pub fn best_team_with_no_conflicts() {
    let answer = Solution::best_team_score(vec![1,3,5,10,15], vec![1,2,3,4,5]);
    println!("{}", answer);
}
