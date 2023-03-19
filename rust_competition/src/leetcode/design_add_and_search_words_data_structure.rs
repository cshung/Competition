struct WordDictionary {
    bitmap: Vec<Vec<Vec<u64>>>,
    count: usize,
}

impl WordDictionary {
    fn new() -> Self {
        return WordDictionary {
            bitmap: vec![vec![vec![0; 157]; 27]; 26],
            count: 0,
        };
    }

    fn add_word(&mut self, word: String) {
        let mut bytes = word.into_bytes();
        let w = self.count / 64;
        let b = self.count % 64;
        let mask = 1 << b;
        let a = 'a' as u8;
        let z = 'z' as u8;
        bytes.push(z + 1);
        for p in 0..bytes.len() {
            let c = (bytes[p] - a) as usize;
            self.bitmap[p][c][w] |= mask;
        }
        self.count = self.count + 1;
    }

    fn search(&self, word: String) -> bool {
        let mut bytes = word.into_bytes();
        let a = 'a' as u8;
        let z = 'z' as u8;
        let dot = '.' as u8;
        bytes.push(z + 1);
        let mut current: Option<Vec<u64>> = None;
        for p in 0..bytes.len() {
            let r = bytes[p];
            if r != dot {
                let c = (r - a) as usize;
                if let Some(current_bitmap) = &mut current {
                    for i in 0..157 {
                        current_bitmap[i] &= self.bitmap[p][c][i];
                    }
                } else {
                    current = Some(self.bitmap[p][c].clone());
                }
            }
        }
        if let Some(current_bitmap) = &current {
            for i in 0..157 {
                if current_bitmap[i] != 0 {
                    return true;
                }
            }
            return false;
        } else {
            return self.count > 0;
        }
    }
}

pub fn design_add_and_search_words_data_structure() {
    let mut word_dictionary = WordDictionary::new();
    word_dictionary.add_word("bad".to_string());
    word_dictionary.add_word("dad".to_string());
    word_dictionary.add_word("mad".to_string());
    println!("{}", word_dictionary.search("pad".to_string()));
    println!("{}", word_dictionary.search("bad".to_string()));
    println!("{}", word_dictionary.search(".ad".to_string()));
    println!("{}", word_dictionary.search("b..".to_string()));
}
