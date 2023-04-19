package merge_strings_alternately

import (
	"fmt"
	"strings"
)

func mergeAlternately(word1 string, word2 string) string {
	i := 0
	j := 0
	builder := strings.Builder{}
	for i < len(word1) || j < len(word2) {
		if i < len(word1) {
			builder.WriteByte(word1[i])
			i = i + 1
		}
		if j < len(word2) {
			builder.WriteByte(word2[j])
			j = j + 1
		}
	}
	return builder.String()
}

func Main() {
	fmt.Println(mergeAlternately("abcd", "pq"))
}
