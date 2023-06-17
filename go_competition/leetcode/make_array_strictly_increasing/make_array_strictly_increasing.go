package make_array_strictly_increasing

import (
	"fmt"
	"sort"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func solveWithLowerBound(lowerBound int, decisionIndex int, availableIndex int, arr1 []int, arr2 []int, memo [][]int) int {
	if decisionIndex == len(arr1) {
		return 0
	}
	toReplaceIndex := sort.Search(len(arr2)-availableIndex, func(i int) bool { return arr2[i+availableIndex] > lowerBound }) + availableIndex

	if arr1[decisionIndex] > lowerBound {
		return solveWithIndex(decisionIndex, toReplaceIndex, arr1, arr2, memo)
	} else {
		if toReplaceIndex == len(arr2) {
			return len(arr1) + 1
		} else {
			return 1 + solveWithLowerBound(arr2[toReplaceIndex], decisionIndex+1, toReplaceIndex+1, arr1, arr2, memo)
		}
	}
}

func solveWithIndex(decisionIndex int, availableIndex int, arr1 []int, arr2 []int, memo [][]int) int {
	if memo[decisionIndex][availableIndex] == 0 {
		answer := solveWithLowerBound(arr1[decisionIndex], decisionIndex+1, availableIndex, arr1, arr2, memo)
		if availableIndex < len(arr2) {
			takeAnswer := 1 + solveWithLowerBound(arr2[availableIndex], decisionIndex+1, availableIndex+1, arr1, arr2, memo)
			answer = min(answer, takeAnswer)
		}
		memo[decisionIndex][availableIndex] = answer + 1
	}
	return memo[decisionIndex][availableIndex] - 1
}

func makeArrayIncreasing(arr1 []int, arr2 []int) int {
	memo := [][]int{}
	for i := 0; i < len(arr1); i++ {
		memo = append(memo, make([]int, len(arr2)+1))
	}
	sort.Ints(arr2)
	answer := solveWithLowerBound(-1, 0, 0, arr1, arr2, memo)
	if answer > len(arr1) {
		return -1
	} else {
		return answer
	}
}

func Main() {
	answer := makeArrayIncreasing([]int{1, 5, 3, 6, 7}, []int{1, 3, 2, 4})
	fmt.Println(answer)
}
