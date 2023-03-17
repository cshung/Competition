use std::collections::HashMap;

struct Trie {
    root: Node,
}

struct Node {
    next: HashMap<u8, Node>,
}

impl Node {
    fn new() -> Self {
        return Node {
            next: HashMap::new(),
        };
    }
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Trie {
    fn new() -> Self {
        return Trie { root: Node::new() };
    }

    fn insert(&mut self, word: String) {
        let mut node = &mut self.root;
        let mut word = word.as_bytes().to_vec();
        word.push(0);
        for i in 0..word.len() {
            node = node.next.entry(word[i]).or_insert(Node::new());
        }
    }

    fn search(&self, word: String) -> bool {
        let mut terminated = word.as_bytes().to_vec();
        terminated.push(0);
        return Self::starts_with_helper(self, &terminated);
    }

    fn starts_with(&self, prefix: String) -> bool {
        let word = prefix.as_bytes();
        return Self::starts_with_helper(self, &word);
    }

    fn starts_with_helper(&self, word: &[u8]) -> bool {
        let mut node = &self.root;

        for i in 0..word.len() {
            if let Some(next) = node.next.get(&word[i]) {
                node = next;
            } else {
                return false;
            }
        }
        return true;
    }
}

pub fn implement_trie_prefix_tree() {
    let mut trie = Trie::new();
    trie.insert("apple".to_string());
    println!("{}", trie.search("apple".to_string()));
    println!("{}", trie.search("app".to_string()));
    println!("{}", trie.starts_with("app".to_string()));
    trie.insert("app".to_string());
    println!("{}", trie.search("app".to_string()));
}
