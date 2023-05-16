package wiggle_sort

import (
	"fmt"
)

func sign(a int, b int) int {
	if a > b {
		return 1
	} else if a < b {
		return -1
	} else {
		return 0
	}
}

func wiggleSort(nums []int) {
	if len(nums) < 2 {
		return
	}
	if nums[0] > nums[1] {
		temp := nums[0]
		nums[0] = nums[1]
		nums[1] = temp
	}
	for i := 0; i+2 < len(nums); i++ {
		direction := sign(nums[i+2], nums[i+1]) // 1 if going up, -1 if going down, 0 is always fine
		up := 2*(i%2) - 1                       // 1 if should go up, -1 if should go down
		if up*direction == -1 {                 // mismatched
			temp := nums[i+1]
			nums[i+1] = nums[i+2]
			nums[i+2] = temp
		}
	}
}

func Main() {
	nums := []int{3, 5, 2, 1, 6, 4}
	wiggleSort(nums)
	for i := 0; i < len(nums); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(nums[i])
	}
	fmt.Println()
}
