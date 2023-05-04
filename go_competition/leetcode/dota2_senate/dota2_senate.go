package dota2_senate

import (
	"fmt"
)

type BoundedCircularQueue struct {
	elements []int
	head     int
	tail     int
	count    int
}

func (q *BoundedCircularQueue) enqueue(element int) {
	q.count = q.count + 1
	if q.count == 1 {
		q.head = len(q.elements) - 1
		q.elements[q.head] = element
		q.tail = q.head - 1
	} else if q.tail != q.head {
		q.elements[q.tail] = element
		q.tail = q.tail - 1
		if q.tail == -1 {
			q.tail = len(q.elements) - 1
		}
	} else {
		panic("Enqueuing to a full queue")
	}
}

func (q *BoundedCircularQueue) dequeue() int {
	q.count = q.count - 1
	if q.count == -1 {
		panic("Dequeuing an empty queue")
	} else {
		answer := q.elements[q.head]
		q.head = q.head - 1
		if q.head == -1 {
			q.head = len(q.elements) - 1
		}
		return answer
	}
}

func (q *BoundedCircularQueue) empty() bool {
	return q.count == 0
}

func (q *BoundedCircularQueue) peek() int {
	if q.count == 0 {
		panic("Peeking an empty queue")
	} else {
		return q.elements[q.head]
	}
}

func circular_distance(base int, target int, n int) int {
	if base >= n {
		panic("Position bigger than length")
	}
	if target >= n {
		panic("Position bigger than length")
	}
	if target >= base {
		return target - base
	} else {
		return target + n - base
	}
}

func predictPartyVictory(senate string) string {
	n := len(senate)
	r_queue := BoundedCircularQueue{make([]int, n), 0, 0, 0}
	d_queue := BoundedCircularQueue{make([]int, n), 0, 0, 0}
	r := "R"[0]
	for i := 0; i < len(senate); i++ {
		if senate[i] == r {
			r_queue.enqueue(i)
		} else {
			d_queue.enqueue(i)
		}
	}

	pos := 0
	for {
		if r_queue.empty() {
			return "Dire"
		} else if d_queue.empty() {
			return "Radiant"
		} else {
			r_pos := r_queue.peek()
			d_pos := d_queue.peek()
			r_dist := circular_distance(pos, r_pos, n)
			d_dist := circular_distance(pos, d_pos, n)
			if r_dist < d_dist {
				pos = r_pos
				r_queue.enqueue(r_queue.dequeue())
				d_queue.dequeue()
			} else if d_dist < r_dist {
				pos = d_pos
				d_queue.enqueue(d_queue.dequeue())
				r_queue.dequeue()
			} else {
				panic("This should not happen")
			}
			pos = pos + 1
			if pos == n {
				pos = 0
			}
		}
	}
}

func Main() {
	answer := predictPartyVictory("RD")
	fmt.Println(answer)
}
