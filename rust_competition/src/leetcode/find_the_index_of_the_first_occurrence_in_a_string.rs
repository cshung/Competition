use std::collections::HashMap;

impl Solution {
    pub fn str_str(haystack: String, needle: String) -> i32 {
        return Self::first_index_of(&haystack, &needle)
            .map(|s| s as i32)
            .unwrap_or(-1);
    }

    fn first_index_of(text: &str, pattern: &str) -> Option<usize> {
        let (good_suffix_shifts, good_suffix_skips) = Self::build_good_suffix_shifts(pattern);
        let bad_character_shifts = Self::build_bad_character_shifts(pattern);
        let text = text.as_bytes();
        let pattern = pattern.as_bytes();
        let text_len = text.len();
        let pattern_len = pattern.len();
        let mut i = 0;
        let mut good_suffix_check = -1;
        let mut good_suffix_skip = 0;

        while i + pattern_len <= text_len {
            let mut pattern_index = pattern_len;
            let mut text_index = i + pattern_index;
            while pattern_index > 0 && text[text_index - 1] == pattern[pattern_index - 1] {
                text_index -= 1;
                pattern_index -= 1;
                if good_suffix_check > 0 {
                    good_suffix_check -= 1;
                    if good_suffix_check == 0 {
                        good_suffix_check = -1;
                        text_index -= good_suffix_skip;
                        pattern_index -= good_suffix_skip;
                    }
                }
            }

            if pattern_index == 0 {
                return Some(i);
            }

            let matched = pattern_len - pattern_index;
            let bad_character_shift = if pattern_index != 0 {
                bad_character_shifts
                    .get(&(text[text_index - 1] as char))
                    .map(|s| s[pattern_index - 1])
                    .unwrap_or(0)
            } else {
                pattern_index as i32
            };

            let good_suffix_shift = good_suffix_shifts[matched];
            if bad_character_shift > (good_suffix_shift as i32) {
                good_suffix_check = -1;
                good_suffix_skip = 0;
                i += bad_character_shift as usize;
            } else {
                good_suffix_check = good_suffix_shift as isize;
                good_suffix_skip = good_suffix_skips[matched];
                i += good_suffix_shift;
            }
        }
        None
    }

    fn build_bad_character_shifts(pattern: &str) -> HashMap<char, Vec<i32>> {
        let mut bad_character_shifts = HashMap::new();
        for (i, c) in pattern.chars().enumerate() {
            let shift = bad_character_shifts
                .entry(c)
                .or_insert(vec![0; pattern.len()]);
            shift[i] = 1;
        }
        for shift in bad_character_shifts.values_mut() {
            let mut last_shift = -1;
            for i in 0..shift.len() {
                if shift[i] == 0 {
                    if last_shift == -1 {
                        shift[i] = (i as i32) + 1;
                    } else {
                        last_shift += 1;
                        shift[i] = last_shift;
                    }
                } else {
                    shift[i] = -1;
                    last_shift = 0;
                }
            }
        }
        bad_character_shifts
    }

    fn find_maximal_suffixes(pattern: &str) -> Vec<usize> {
        let length = pattern.len();
        let mut maximal_suffix_lengths = vec![0; length];
        let mut maximal_start = length;
        let mut maximal_end = length;
        for current_end in (1..length).rev() {
            let mut current_start = current_end;
            let mut suffix_start = length;
            if maximal_start < current_end && current_end <= maximal_end {
                let known_start = maximal_start + length - maximal_end;
                let known_end = current_end + length - maximal_end;
                let known_suffix_length = maximal_suffix_lengths[known_end - 1];
                let known_suffix_start = known_end - known_suffix_length;
                let max_start = std::cmp::max(known_suffix_start, known_start);
                let max_end = known_end;
                let max_length = max_end - max_start;
                current_start -= max_length;
                suffix_start -= max_length;
            }
            current_start = current_start + 1;
            loop {
                current_start -= 1;
                suffix_start -= 1;
                if current_start == 0
                    || pattern.as_bytes()[current_start - 1] != pattern.as_bytes()[suffix_start]
                {
                    break;
                }
            }
            if current_start < maximal_start {
                maximal_start = current_start;
                maximal_end = current_end;
            }
            maximal_suffix_lengths[current_end - 1] = current_end - current_start;
        }
        maximal_suffix_lengths[length - 1] = length;
        return maximal_suffix_lengths;
    }

    fn find_longest_border(maximal_suffix_lengths: &[usize]) -> Vec<usize> {
        let length = maximal_suffix_lengths.len();
        let mut longest_border = vec![0; length];
        let mut border_length = 0;
        for i in 0..length {
            if maximal_suffix_lengths[i] == i + 1 {
                border_length = i + 1;
            }
            longest_border[i] = border_length;
        }
        longest_border
    }

    fn build_good_suffix_shifts(pattern: &str) -> (Vec<usize>, Vec<usize>) {
        let length = pattern.len();
        let maximal_suffix_lengths = Self::find_maximal_suffixes(pattern);
        let longest_border = Self::find_longest_border(&maximal_suffix_lengths);
        let mut shifts = vec![0; length + 1];
        let mut skips = vec![0; length + 1];
        shifts[0] = 1;
        skips[0] = 0;

        for i in (0..length - 1).rev() {
            let maximal_suffix_length = maximal_suffix_lengths[i];
            if maximal_suffix_length != 0 {
                if shifts[maximal_suffix_length] == 0 {
                    shifts[maximal_suffix_length] = length - 1 - i;
                    skips[maximal_suffix_length] = maximal_suffix_length;
                }
            }
        }

        for i in 1..length {
            if shifts[i] == 0 {
                if longest_border[i - 1] != 0 {
                    shifts[i] = length - longest_border[i - 1];
                    skips[i] = longest_border[i - 1];
                }
            }
        }

        if length > 1 && longest_border[length - 2] != 0 {
            shifts[length] = longest_border[length - 2] - 1;
            skips[length] = longest_border[length - 2];
        }

        for i in 0..=length {
            if shifts[i] == 0 {
                shifts[i] = length;
                skips[i] = 0;
            }
        }

        (shifts, skips)
    }
}

struct Solution {}

pub fn find_the_index_of_the_first_occurrence_in_a_string() {
    let answer = Solution::str_str("sadbutsad".to_string(), "sad".to_string());
    println!("{}", answer);
}
