package minimum_cost_to_make_array_equal

import (
	"fmt"
	"sort"
)

// Define a type to hold your two slices
type SyncedSlices struct {
	keys   []int
	values []int
}

// Implement sort.Interface for SyncedSlices

func (ss *SyncedSlices) Len() int {
	return len(ss.keys)
}

func (ss *SyncedSlices) Less(i, j int) bool {
	return ss.keys[i] < ss.keys[j]
}

func (ss *SyncedSlices) Swap(i, j int) {
	ss.keys[i], ss.keys[j] = ss.keys[j], ss.keys[i]
	ss.values[i], ss.values[j] = ss.values[j], ss.values[i]
}

func minCost(nums []int, cost []int) int64 {
	ss := &SyncedSlices{
		keys:   nums,
		values: cost,
	}

	// Sort the keys and keep the values in sync
	sort.Sort(ss)

	s := int64(0)
	running_costs := []int64{}
	for i := 0; i < len(nums); i++ {
		c := int64(cost[i])
		s += c
		running_costs = append(running_costs, s)
	}

	current_cost := int64(0)
	for i := 1; i < len(nums); i++ {
		c := int64(cost[i])
		d := int64(nums[i] - nums[0])
		current_cost += c * d
	}

	for i := 1; i < len(nums); i++ {
		delta := running_costs[i-1]*2 - s
		if delta >= 0 {
			break
		} else {
			d := int64(nums[i] - nums[i-1])
			current_cost = current_cost + delta*d
		}
	}

	return current_cost
}

func Main() {
	answer := minCost([]int{1, 3, 5, 2}, []int{2, 3, 1, 14})
	fmt.Println(answer)
}
