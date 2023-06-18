package sentence_similarity

import (
	"fmt"
)

type Pair struct {
	first  int
	second int
}

func id(s string, ids map[string]int) int {
	result, ok := ids[s]
	if !ok {
		result = len(ids)
		ids[s] = result
	}
	return result
}

func areSentencesSimilar(sentence1 []string, sentence2 []string, similarPairs [][]string) bool {
	ids := make(map[string]int)
	pairs := make(map[Pair]struct{})
	if len(sentence1) != len(sentence2) {
		return false
	}
	for i := 0; i < len(similarPairs); i++ {
		f := id(similarPairs[i][0], ids)
		s := id(similarPairs[i][1], ids)
		pairs[Pair{f, s}] = struct{}{}
		pairs[Pair{s, f}] = struct{}{}
	}
	l := len(sentence1)
	for i := 0; i < l; i++ {
		s1 := id(sentence1[i], ids)
		s2 := id(sentence2[i], ids)
		if s1 != s2 {
			_, ok := pairs[Pair{s1, s2}]
			if !ok {
				return false
			}
		}
	}
	return true
}

func Main() {
	answer := areSentencesSimilar([]string{"great", "acting", "skills"}, []string{"fine", "drama", "talent"}, [][]string{[]string{"great", "fine"}, []string{"drama", "acting"}, []string{"skills", "talent"}})
	fmt.Println(answer)
}
