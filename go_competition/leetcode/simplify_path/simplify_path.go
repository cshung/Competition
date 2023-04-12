package simplify_path

import (
	"fmt"
	"strings"
)

func simplifyPath(path string) string {
	builder := strings.Builder{}
	var tokens []string
	for _, char := range path {
		if char == '/' {
			if builder.Len() > 0 {
				element := builder.String()
				if element == ".." {
					if len(tokens) > 0 {
						tokens = tokens[:len(tokens)-1]
					}
				} else if element != "." {
					tokens = append(tokens, element)
				}
				builder.Reset()
			}
		} else {
			builder.WriteString(string(char))
		}
	}
	if builder.Len() > 0 {
		element := builder.String()
		if element == ".." {
			if len(tokens) > 0 {
				tokens = tokens[:len(tokens)-1]
			}
		} else if element != "." {
			tokens = append(tokens, element)
		}
	}
	builder.Reset()
	for i := 0; i < len(tokens); i++ {
		builder.WriteString("/")
		builder.WriteString(tokens[i])
	}
	if builder.Len() == 0 {
		builder.WriteString("/")
	}
	return builder.String()
}

func Simplify_path() {
	fmt.Println(simplifyPath("/home/"))
}
