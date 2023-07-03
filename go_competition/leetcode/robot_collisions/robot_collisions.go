package robot_collisions

import (
	"container/heap"
	"fmt"
	"sort"
)

type SyncedSlices struct {
	positions  []int
	healths    []int
	directions []bool
	origin     []int
}

// Implement sort.Interface for SyncedSlices

func (ss *SyncedSlices) Len() int {
	return len(ss.positions)
}

func (ss *SyncedSlices) Less(i, j int) bool {
	return ss.positions[i] < ss.positions[j]
}

func (ss *SyncedSlices) Swap(i, j int) {
	ss.positions[i], ss.positions[j] = ss.positions[j], ss.positions[i]
	ss.healths[i], ss.healths[j] = ss.healths[j], ss.healths[i]
	ss.directions[i], ss.directions[j] = ss.directions[j], ss.directions[i]
	ss.origin[i], ss.origin[j] = ss.origin[j], ss.origin[i]
}

type Event struct {
	time  int
	index int
}

type EventHeap []Event

func (h EventHeap) Len() int           { return len(h) }
func (h EventHeap) Less(i, j int) bool { return h[i].time < h[j].time }
func (h EventHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *EventHeap) Push(x interface{}) {
	*h = append(*h, x.(Event))
}

func (h *EventHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func survivedRobotsHealths(positions []int, healths []int, directions string) []int {
	l := "L"[0]
	n := len(positions)
	dirs := make([]bool, n)
	next := make([]int, n+2)
	prev := make([]int, n+2)
	origin := make([]int, n)
	for i := 0; i < n; i++ {
		next[i+1] = i + 2
		prev[i+1] = i
		dirs[i] = directions[i] == l
		origin[i] = i
	}
	next[0] = 1
	prev[n+1] = n
	sort.Sort(&SyncedSlices{positions, healths, dirs, origin})
	events := EventHeap{}
	for i := 1; i < n; i++ {
		if !dirs[i-1] && dirs[i] {
			heap.Push(&events, Event{(positions[i] - positions[i-1]) / 2, i})
		}
	}
	time := 0
	for len(events) > 0 {
		event := heap.Pop(&events).(Event)
		time = event.time
		rightIndex := event.index
		rightAddress := rightIndex + 1
		leftAddress := prev[rightAddress]
		if leftAddress == 0 {
			panic(1)
		}
		leftIndex := leftAddress - 1

		leftHealth := healths[leftIndex]
		rightHealth := healths[rightIndex]

		newLeftAddress := 0
		newRightAddress := 0
		if leftHealth > rightHealth {
			newLeftAddress = leftAddress
			newRightAddress = next[rightAddress]
			healths[leftIndex]--
			healths[rightIndex] = 0
		} else if leftHealth < rightHealth {
			newLeftAddress = prev[leftAddress]
			newRightAddress = rightAddress
			healths[leftIndex] = 0
			healths[rightIndex]--
		} else {
			newLeftAddress = prev[leftAddress]
			newRightAddress = next[rightAddress]
			healths[leftIndex] = 0
			healths[rightIndex] = 0
		}
		next[newLeftAddress] = newRightAddress
		prev[newRightAddress] = newLeftAddress
		if (newLeftAddress != 0) && (newRightAddress != (n + 1)) {
			newLeftIndex := newLeftAddress - 1
			newRightIndex := newRightAddress - 1
			if (!dirs[newLeftIndex]) && dirs[newRightIndex] {
				newRightPosition := (positions[newRightIndex] - time)
				newLeftPosition := (positions[newLeftIndex] + time)
				heap.Push(&events, Event{time + (newRightPosition-newLeftPosition)/2, newRightIndex})
			}
		}
	}
	for i := 0; i < n; i++ {
		positions[origin[i]] = healths[i]
	}
	answer := []int{}
	for i := 0; i < n; i++ {
		if positions[i] != 0 {
			answer = append(answer, positions[i])
		}
	}
	return answer
}

func Main() {
	answer := survivedRobotsHealths([]int{5, 4, 3, 2, 1}, []int{2, 17, 9, 15, 10}, "RRRRR")
	fmt.Println(answer)
}
