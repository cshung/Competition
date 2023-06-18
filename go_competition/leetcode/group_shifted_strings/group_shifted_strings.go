package group_shifted_strings

import (
	"fmt"
	"strconv"
	"strings"
)

func groupStrings(input []string) [][]string {
	groups := make(map[string][]string)
	for i := 0; i < len(input); i++ {
		s := input[i]
		diff := []string{}
		for j := 0; j < len(s)-1; j++ {
			dist := ((s[j+1] - s[j]) + 26) % 26
			diff = append(diff, strconv.Itoa(int(dist)))
		}
		key := strings.Join(diff, ",")
		items, ok := groups[key]
		if !ok {
			items = []string{}
		}
		items = append(items, s)
		groups[key] = items
	}
	answers := [][]string{}
	for _, items := range groups {
		answers = append(answers, items)
	}
	return answers
}

func Main() {
	answers := groupStrings([]string{"abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"})
	for i := 0; i < len(answers); i++ {
		for j := 0; j < len(answers[i]); j++ {
			if j > 0 {
				fmt.Print(", ")
			}
			fmt.Print(answers[i][j])
		}
		fmt.Println()
	}
}
