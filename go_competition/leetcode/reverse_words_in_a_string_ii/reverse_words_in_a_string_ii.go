package reverse_words_in_a_string_ii

import (
	"fmt"
)

func reverseWords(s []byte) {
	n := len(s)
	i := 0
	j := n - 1
	for i < j {
		t := s[i]
		s[i] = s[j]
		s[j] = t
		i++
		j--
	}

	i = 0
	for {
		for j = i; j < n && s[j] != ' '; j++ {

		}
		p := i
		q := j - 1
		for p < q {
			t := s[p]
			s[p] = s[q]
			s[q] = t
			p++
			q--
		}
		if j == n {
			break
		}
		i = j + 1
	}
}

func Main() {
	b := []byte("the sky is blue")
	reverseWords(b)
	fmt.Println(string(b))
}
