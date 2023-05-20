package evaluate_division

import (
	"fmt"
)

func dfs(from string, to string, v float64, adj map[string]map[string]float64, visited map[string]struct{}) float64 {
	visited[from] = struct{}{}
	if from == to {
		return v
	}
	neighbors := adj[from]
	for neighbor, neighborValue := range neighbors {
		_, neighborVisited := visited[neighbor]
		if !neighborVisited {
			neighborResult := dfs(neighbor, to, v*neighborValue, adj, visited)
			if neighborResult != -1 {
				return neighborResult
			}
		}
	}
	return -1
}

func calcEquation(equations [][]string, values []float64, queries [][]string) []float64 {
	zeroVariables := map[string]struct{}{}
	adj := map[string]map[string]float64{}
	for i := 0; i < len(equations); i++ {
		numerator := equations[i][0]
		denominator := equations[i][1]
		if numerator != denominator {
			value := values[i]
			if value == 0.0 {
				zeroVariables[numerator] = struct{}{}
			} else {
				numeratorList, numeratorFound := adj[numerator]
				if !numeratorFound {
					numeratorList = map[string]float64{}
					adj[numerator] = numeratorList
				}
				numeratorList[denominator] = value
				denominatorList, denominatorFound := adj[denominator]
				if !denominatorFound {
					denominatorList = map[string]float64{}
					adj[denominator] = denominatorList
				}
				denominatorList[numerator] = 1 / value
			}
		}
	}
	answers := []float64{}
	for i := 0; i < len(queries); i++ {
		numerator := queries[i][0]
		denominator := queries[i][1]
		answer := 0.0
		_, zeroFound := zeroVariables[numerator]
		if !zeroFound {
			_, adjFoundNumerator := adj[numerator]
			_, adjFoundDenominator := adj[denominator]
			if adjFoundNumerator && adjFoundDenominator {
				visited := map[string]struct{}{}
				answer = dfs(numerator, denominator, 1.0, adj, visited)
			} else {
				answer = -1
			}
		}
		answers = append(answers, answer)
	}
	return answers
}

func Main() {
	answers := calcEquation([][]string{[]string{"a", "b"}, []string{"b", "c"}}, []float64{2.0, 3.0}, [][]string{[]string{"a", "c"}, []string{"b", "a"}, []string{"a", "e"}, []string{"a", "a"}, []string{"x", "x"}})
	for i := 0; i < len(answers); i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(answers[i])
	}
	fmt.Println()
}
