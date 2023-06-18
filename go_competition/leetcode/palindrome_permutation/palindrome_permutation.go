package palindrome_permutation

import (
	"fmt"
)

func canPermutePalindrome(s string) bool {
	oddCount := 0
	histogram := make(map[rune]int)
	for _, char := range s {
		count, ok := histogram[char]
		if !ok {
			count = 0
		}
		count = count + 1
		histogram[char] = count
		oddCount += (count%2)*2 - 1
	}
	return oddCount < 2
}

func Main() {
	answer := canPermutePalindrome("code")
	fmt.Println(answer)
}
