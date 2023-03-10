use library::rand::Rand;

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

struct Solution {
    head: Option<Box<ListNode>>,
    length: i32,
    rng: Rand,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Solution {
    fn new(head: Option<Box<ListNode>>) -> Self {
        Solution {
            head: head,
            length: 0,
            rng: Rand::new(0),
        }
    }

    fn get_random(&mut self) -> i32 {
        loop {
            let mut n = if self.length == 0 { 10000 } else { self.length };
            let mut count = 0;
            let mut cur = &self.head;
            loop {
                if let Some(node) = cur {
                    count = count + 1;
                    if self.rng.rand_range(1, n) == 1 {
                        return node.val;
                    } else {
                        cur = &node.next;
                    }
                    n = n - 1;
                } else {
                    break;
                }
            }
            self.length = count;
        }
    }
}

pub fn linked_list_random_node() {
    let mut a = Box::new(ListNode::new(1));
    let mut b = Box::new(ListNode::new(2));
    let c = Box::new(ListNode::new(3));
    b.next = Some(c);
    a.next = Some(b);

    let mut s = Solution::new(Some(a));
    let mut one = 0;
    let mut two = 0;
    let mut three = 0;
    for _i in 0..100000 {
        let answer = s.get_random();
        if answer == 1 {
            one += 1;
        } else if answer == 2 {
            two += 1;
        } else if answer == 3 {
            three += 1;
        } else {
            println!("Game over");
        }
    }
    println!("{} {} {}", one, two, three);
}
