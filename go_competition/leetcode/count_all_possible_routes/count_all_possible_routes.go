package count_all_possible_routes

import (
	"fmt"
)

func abs(i int) int {
	if i < 0 {
		return -i
	}
	return i
}

func countRoutes(locations []int, start int, finish int, fuel int) int {
	num_locations := len(locations)
	counts := make([][]int, num_locations)
	for i := 0; i < num_locations; i++ {
		counts[i] = make([]int, fuel+1)
	}
	counts[start][fuel] = 1
	for f := fuel; f >= 0; f-- {
		for l := 0; l < num_locations; l++ {
			count := 0
			for p := 0; p < num_locations; p++ {
				dist := abs(locations[l] - locations[p])
				prev_fuel := f + dist
				if f+dist <= fuel {
					count = count + counts[p][prev_fuel]
					count = count % 1000000007
				}
			}
			counts[l][f] = count
		}
	}
	answer := 0
	for f := fuel; f >= 0; f-- {
		answer = answer + counts[finish][f]
		answer = answer % 1000000007
	}
	return answer
}

func Main() {
	answer := countRoutes([]int{2, 3, 6, 8, 5}, 1, 3, 5)
	fmt.Println(answer)
}
