package find_smallest_letter_greater_than_target

import (
	"fmt"
	"sort"
)

func nextGreatestLetter(letters []byte, target byte) byte {
	index := sort.Search(len(letters), func(i int) bool { return letters[i] > target })
	return letters[index]
}

func Main() {
	answer := nextGreatestLetter([]byte{'c', 'f', 'j'}, 'c')
	fmt.Println(answer)
}
