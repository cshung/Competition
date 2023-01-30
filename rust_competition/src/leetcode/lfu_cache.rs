use std::cell::RefCell;
use std::collections::HashMap;
use std::convert::TryInto;
use std::rc::Rc;
use std::rc::Weak;

// The cache owns the head and tail of the Bucket list
struct LFUCache {
    capacity: usize,
    head: Rc<RefCell<Bucket>>,
    tail: Rc<RefCell<Bucket>>,
    boxes: HashMap<i32, Weak<RefCell<KeyBox>>>,
}

// The Bucket owns the head and tail of the KeyBox list
// The Bucket owns the next Bucket
struct Bucket {
    frequency: usize,
    next: Option<Rc<RefCell<Bucket>>>,
    prev: Option<Weak<RefCell<Bucket>>>,
    head: Rc<RefCell<KeyBox>>,
    tail: Rc<RefCell<KeyBox>>,
}

// The KeyBox owns the next KeyBox
struct KeyBox {
    key: i32,
    value: i32,
    prev: Option<Weak<RefCell<KeyBox>>>,
    next: Option<Rc<RefCell<KeyBox>>>,
    bucket: Option<Weak<RefCell<Bucket>>>,
}

impl LFUCache {
    fn new(capacity: i32) -> Self {
        let head = Bucket::new(0);
        let tail = Bucket::new(0);
        let head = Rc::new(RefCell::new(head));
        let tail = Rc::new(RefCell::new(tail));
        head.borrow_mut().next = Some(Rc::clone(&tail));
        tail.borrow_mut().prev = Some(Rc::downgrade(&Rc::clone(&head)));
        return LFUCache {
            capacity: capacity.try_into().unwrap(),
            head: head,
            tail: tail,
            boxes: HashMap::new(),
        };
    }

    fn get(&mut self, key: i32) -> i32 {
        if self.capacity == 0 {
            return -1;
        }
        if let Some(old_box_weak) = self.boxes.get_mut(&key) {
            let old_box = Rc::clone(&old_box_weak.upgrade().unwrap());
            self.promote_box(Rc::clone(&old_box));
            return old_box.borrow_mut().value;
        } else {
            return -1;
        }
    }

    fn put(&mut self, key: i32, value: i32) {
        if self.capacity == 0 {
            return;
        }
        if let Some(old_box_weak) = self.boxes.get_mut(&key) {
            let old_box = Rc::clone(&old_box_weak.upgrade().unwrap());
            self.promote_box(Rc::clone(&old_box));
            old_box.borrow_mut().value = value;
        } else {
            if self.boxes.len() == self.capacity {
                let head = Rc::clone(&self.head);
                let first_bucket = head.borrow().next();
                let victim_box = first_bucket.borrow().head.borrow().next();
                self.remove_box(Rc::clone(&victim_box));
                self.boxes.remove(&victim_box.borrow().key);
            }
            let new_box = KeyBox {
                key: key,
                value: value,
                prev: None,
                next: None,
                bucket: None,
            };
            let new_box = Rc::new(RefCell::new(new_box));
            self.boxes.insert(key, Rc::downgrade(&new_box));
            let head = Rc::clone(&self.head);
            let head_next = head.borrow().next();
            let mut need_first_bucket = false;
            if Rc::ptr_eq(&head_next, &self.tail) {
                need_first_bucket = true;
            } else {
                if head_next.borrow().frequency != 1 {
                    need_first_bucket = true;
                }
            }
            if need_first_bucket {
                Bucket::add_next_bucket(Rc::clone(&head), 1);
            }
            let first_bucket = head.borrow().next();
            new_box.borrow_mut().bucket = Some(Rc::downgrade(&first_bucket));
            Bucket::add_box(Rc::clone(&first_bucket), new_box);
        }
    }

    fn promote_box(&self, old_box: Rc<RefCell<KeyBox>>) {
        let old_bucket = old_box.borrow().bucket();
        let next_bucket = old_bucket.borrow().next();
        let old_frequency = old_bucket.borrow().frequency;
        let new_frequency = old_frequency + 1;
        let mut need_next_bucket = false;
        if Rc::ptr_eq(&next_bucket, &self.tail) {
            need_next_bucket = true;
        } else {
            if next_bucket.borrow().frequency != new_frequency {
                need_next_bucket = true;
            }
        }
        if need_next_bucket {
            Bucket::add_next_bucket(Rc::clone(&old_bucket), new_frequency);
        }
        let next_bucket = old_bucket.borrow().next();
        self.remove_box(Rc::clone(&old_box));
        Bucket::add_box(next_bucket, Rc::clone(&old_box));
    }

    fn remove_box(&self, old_box: Rc<RefCell<KeyBox>>) {
        let old_box_prev = old_box.borrow().prev();
        let old_box_next = Rc::clone(&old_box.borrow().next());
        let old_bucket = old_box.borrow().bucket();
        let prev_bucket = old_bucket.borrow().prev();
        let next_bucket = old_bucket.borrow().next();
        old_box_prev.borrow_mut().next = Some(Rc::clone(&old_box_next));
        old_box_next.borrow_mut().prev = Some(Rc::downgrade(&old_box_prev));
        old_box.borrow_mut().prev = None;
        old_box.borrow_mut().next = None;
        let old_bucket_head = Rc::clone(&old_bucket.borrow().head);
        let old_bucket_tail = Rc::clone(&old_bucket.borrow().tail);
        let old_bucket_head_next = Rc::clone(&old_bucket_head.borrow().next());
        if Rc::ptr_eq(&old_bucket_head_next, &old_bucket_tail) {
            prev_bucket.borrow_mut().next = Some(Rc::clone(&next_bucket));
            next_bucket.borrow_mut().prev = Some(Rc::downgrade(&prev_bucket));
            old_bucket.borrow_mut().next = None;
            old_bucket.borrow_mut().prev = None;
        }
    }

    fn print(&self) {
        println!("---------------");
        let tail_bucket = Rc::clone(&self.tail);
        let mut bucket = self.head.borrow().next();
        while !Rc::ptr_eq(&bucket, &tail_bucket) {
            println!("Bucket {}", bucket.borrow().frequency);
            let mut current_box = bucket.borrow().head.borrow().next();
            let tail_box = Rc::clone(&bucket.borrow().tail);
            while !Rc::ptr_eq(&current_box, &tail_box) {
                println!(
                    "  {} -> {}",
                    current_box.borrow().key,
                    current_box.borrow().value
                );
                let next_box = current_box.borrow().next();
                current_box = next_box;
            }
            let next_bucket = bucket.borrow().next();
            bucket = next_bucket;
        }
        println!("---------------");
    }
}

impl Bucket {
    fn new(frequency: usize) -> Self {
        let head = KeyBox {
            key: -1,
            value: -1,
            prev: None,
            next: None,
            bucket: None,
        };
        let tail = KeyBox {
            key: -1,
            value: -1,
            prev: None,
            next: None,
            bucket: None,
        };
        let head = Rc::new(RefCell::new(head));
        let tail = Rc::new(RefCell::new(tail));
        head.borrow_mut().next = Some(Rc::clone(&tail));
        tail.borrow_mut().prev = Some(Rc::downgrade(&Rc::clone(&head)));
        return Bucket {
            frequency: frequency,
            next: None,
            prev: None,
            head: head,
            tail: tail,
        };
    }

    fn add_next_bucket(self_ref: Rc<RefCell<Bucket>>, frequency: usize) {
        let self_next = self_ref.borrow().next();
        let new_freq = Bucket::new(frequency);
        let new_freq = Rc::new(RefCell::new(new_freq));
        new_freq.borrow_mut().prev = Some(Rc::downgrade(&self_ref));
        new_freq.borrow_mut().next = Some(Rc::clone(&self_next));
        self_next.borrow_mut().prev = Some(Rc::downgrade(&new_freq));
        self_ref.borrow_mut().next = Some(Rc::clone(&new_freq));
    }

    fn add_box(self_ref: Rc<RefCell<Bucket>>, new_box: Rc<RefCell<KeyBox>>) {
        let tail_box = Rc::clone(&self_ref.borrow().tail);
        let tail_prev = tail_box.borrow().prev();
        new_box.borrow_mut().bucket = Some(Rc::downgrade(&self_ref));
        new_box.borrow_mut().prev = Some(Rc::downgrade(&tail_prev));
        new_box.borrow_mut().next = Some(Rc::clone(&tail_box));
        tail_box.borrow_mut().prev = Some(Rc::downgrade(&new_box));
        tail_prev.borrow_mut().next = Some(Rc::clone(&new_box));
    }

    fn prev(&self) -> Rc<RefCell<Bucket>> {
        return Rc::clone(&self.prev.as_ref().unwrap().upgrade().unwrap());
    }

    fn next(&self) -> Rc<RefCell<Bucket>> {
        return Rc::clone(&self.next.as_ref().unwrap());
    }
}

impl KeyBox {
    fn prev(&self) -> Rc<RefCell<KeyBox>> {
        return Rc::clone(&self.prev.as_ref().unwrap().upgrade().unwrap());
    }
    fn next(&self) -> Rc<RefCell<KeyBox>> {
        return Rc::clone(&self.next.as_ref().unwrap());
    }
    fn bucket(&self) -> Rc<RefCell<Bucket>> {
        return Rc::clone(&self.bucket.as_ref().unwrap().upgrade().unwrap());
    }
}

pub fn lfu_cache() {
    let mut cache = LFUCache::new(2); //
    cache.put(1, 1);
    println!("put(1, 1)");
    cache.print(); //
    cache.put(2, 2);
    println!("put(2, 2)");
    cache.print(); //
    println!("get(1) = {}", cache.get(1));
    cache.print(); //
    cache.put(3, 3);
    println!("put(3, 3)");
    cache.print(); //
    println!("get(2) = {}", cache.get(2));
    cache.print(); //
    println!("get(3) = {}", cache.get(3));
    cache.print(); //
    cache.put(4, 4);
    println!("put(4, 4)");
    cache.print(); //
    println!("get(1) = {}", cache.get(1));
    cache.print(); //
    println!("get(3) = {}", cache.get(3));
    cache.print(); //
    println!("get(4) = {}", cache.get(4));
    cache.print(); //
}
