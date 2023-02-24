use std::cmp;

pub struct MinMaxHeap {
    m_capacity: usize,
    m_size: usize,
    m_storage: Vec<i32>,
}

impl MinMaxHeap {
    pub fn new(capacity: usize) -> MinMaxHeap {
        MinMaxHeap {
            m_capacity: capacity,
            m_size: 0,
            m_storage: vec![0; capacity],
        }
    }

    pub fn get_size(&self) -> usize {
        self.m_size
    }

    pub fn try_insert(&mut self, value: i32) -> bool {
        if self.m_size == self.m_capacity {
            return false;
        }

        // Step 1: Place the value in the last element
        self.m_storage[self.m_size] = value;
        self.m_size += 1;
        let node_number = self.m_size;

        // Step 2: Bubbling the value up
        if self.is_min_node(node_number) {
            self.bubble_up_min_node(node_number);
        } else {
            self.bubble_up_max_node(node_number);
        }

        true
    }

    fn has_parent_node(&self, node_index: usize) -> bool {
        node_index != 1
    }

    fn parent_node(&self, node_index: usize) -> usize {
        node_index / 2
    }

    fn is_min_node(&self, node_index: usize) -> bool {
        if node_index == 1 {
            true
        } else {
            !self.is_min_node(self.parent_node(node_index))
        }
    }

    fn bubble_up_min_node(&mut self, node_number: usize) {
        if self.has_parent_node(node_number) {
            let max_node_number = self.parent_node(node_number);
            if self.m_storage[max_node_number - 1] < self.m_storage[node_number - 1] {
                self.m_storage.swap(max_node_number - 1, node_number - 1);
                self.bubble_up_max_node(max_node_number);
            } else if self.has_parent_node(max_node_number) {
                let min_node_number = self.parent_node(max_node_number);
                if self.m_storage[min_node_number - 1] > self.m_storage[node_number - 1] {
                    self.m_storage.swap(min_node_number - 1, node_number - 1);
                    self.bubble_up_min_node(min_node_number);
                }
            }
        }
    }

    fn bubble_up_max_node(&mut self, node_number: usize) {
        if self.has_parent_node(node_number) {
            let min_node_number = self.parent_node(node_number);
            if self.m_storage[min_node_number - 1] > self.m_storage[node_number - 1] {
                self.m_storage.swap(min_node_number - 1, node_number - 1);
                self.bubble_up_min_node(min_node_number);
            } else if self.has_parent_node(min_node_number) {
                let max_node_number = self.parent_node(min_node_number);
                if self.m_storage[max_node_number - 1] < self.m_storage[node_number - 1] {
                    self.m_storage.swap(max_node_number - 1, node_number - 1);
                    self.bubble_up_max_node(max_node_number);
                }
            }
        }
    }

    pub fn try_delete_min(&mut self, min_value: &mut i32) -> bool {
        if self.m_size == 0 {
            return false;
        } else {
            *min_value = self.m_storage[0];
            self.m_size -= 1;
            self.m_storage[0] = self.m_storage[self.m_size];
            self.bubble_down_min_node(1);
            return true;
        }
    }

    fn bubble_down_min_node(&mut self, node_number: usize) {
        let mut min_value = self.m_storage[node_number - 1];
        let mut is_next_node_type_max_node = true;
        let mut next_node_number = node_number;

        for i in 0..2 {
            let candidate_node_number = node_number * 2 + i;
            if candidate_node_number > self.m_size {
                break;
            } else {
                let candidate_value = self.m_storage[candidate_node_number - 1];
                if candidate_value < min_value {
                    min_value = candidate_value;
                    next_node_number = candidate_node_number;
                }
            }
        }

        for i in 0..4 {
            let candidate_node_number = node_number * 4 + i;
            if candidate_node_number > self.m_size {
                break;
            } else {
                let candidate_value = self.m_storage[candidate_node_number - 1];
                if candidate_value < min_value {
                    min_value = candidate_value;
                    next_node_number = candidate_node_number;
                    is_next_node_type_max_node = false;
                }
            }
        }

        if next_node_number != node_number {
            self.m_storage.swap(node_number - 1, next_node_number - 1);
            if is_next_node_type_max_node {
                self.bubble_down_max_node(next_node_number);
            } else {
                self.bubble_down_min_node(next_node_number);
            }
        }
    }

    pub fn try_delete_max(&mut self, max_value: &mut i32) -> bool {
        if self.m_size == 0 {
            return false;
        } else if self.m_size == 1 {
            *max_value = self.m_storage[0];
            self.m_size -= 1;
            return true;
        } else if self.m_size == 2 {
            *max_value = self.m_storage[1];
            self.m_size -= 1;
            return true;
        } else {
            let max_node_number = if self.m_storage[1] > self.m_storage[2] {
                2
            } else {
                3
            };
            self.m_size -= 1;
            *max_value = self.m_storage[max_node_number - 1];
            self.m_storage[max_node_number - 1] = self.m_storage[self.m_size];
            self.bubble_down_max_node(max_node_number);
            return true;
        }
    }

    fn bubble_down_max_node(&mut self, node_number: usize) {
        let mut max_value = self.m_storage[node_number - 1];
        let mut is_next_node_type_min_node = true;
        let mut next_node_number = node_number;
        for i in 0..2 {
            let candidate_node_number = node_number * 2 + i;
            if candidate_node_number > self.m_size {
                break;
            } else {
                let candidate_value = self.m_storage[candidate_node_number - 1];
                if candidate_value > max_value {
                    max_value = candidate_value;
                    next_node_number = candidate_node_number;
                }
            }
        }

        for i in 0..4 {
            let candidate_node_number = node_number * 4 + i;
            if candidate_node_number > self.m_size {
                break;
            } else {
                let candidate_value = self.m_storage[candidate_node_number - 1];
                if candidate_value > max_value {
                    max_value = candidate_value;
                    next_node_number = candidate_node_number;
                    is_next_node_type_min_node = false;
                }
            }
        }

        if next_node_number != node_number {
            self.m_storage.swap(node_number - 1, next_node_number - 1);
            if is_next_node_type_min_node {
                self.bubble_down_min_node(next_node_number);
            } else {
                self.bubble_down_max_node(next_node_number);
            }
        }
    }

    #[allow(dead_code)]
    pub fn try_get_min(&self) -> Option<i32> {
        if self.m_size == 0 {
            return None;
        } else {
            return Some(self.m_storage[0]);
        }
    }

    #[allow(dead_code)]
    pub fn try_get_max(&self) -> Option<i32> {
        match self.m_size {
            0 => None,
            1 => Some(self.m_storage[0]),
            2 => Some(self.m_storage[1]),
            _ => Some(cmp::max(self.m_storage[0], self.m_storage[1])),
        }
    }
}
