package tallest_billboard

import (
	"fmt"
)

func tallestBillboard(rods []int) int {
	pairs := make(map[int]int)
	pairs[0] = 0
	n := len(rods)
	for i := 0; i < n; i++ {
		rod := rods[i]
		new_pairs := []int{}
		for diff, tall := range pairs {
			short := tall - diff
			new_tall_1 := tall + rod
			new_short_1 := short

			new_tall_2 := tall
			new_short_2 := short + rod
			if new_tall_2 < new_short_2 {
				new_tall_2, new_short_2 = new_short_2, new_tall_2
			}

			new_diff_1 := new_tall_1 - new_short_1
			if new_diff_1 <= 2500 {
				new_pairs = append(new_pairs, new_diff_1)
				new_pairs = append(new_pairs, new_tall_1)
			}

			new_diff_2 := new_tall_2 - new_short_2
			if new_diff_2 <= 2500 {
				new_pairs = append(new_pairs, new_diff_2)
				new_pairs = append(new_pairs, new_tall_2)
			}
		}
		for j := 0; j < len(new_pairs); j += 2 {
			diff := new_pairs[j]
			tall := new_pairs[j+1]
			existing, ok := pairs[diff]
			if !ok || tall > existing {
				pairs[diff] = tall
			}
		}
	}
	return pairs[0]
}

func Main() {
	answer := tallestBillboard([]int{1, 2, 3, 6})
	fmt.Println(answer)
}
