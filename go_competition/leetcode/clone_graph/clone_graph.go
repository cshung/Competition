package clone_graph

import "fmt"

type Node struct {
	Val       int
	Neighbors []*Node
}

func clone(clones map[int]*Node, node *Node) *Node {
	answer := clones[node.Val]
	if answer == nil {
		n := len(node.Neighbors)
		answer = &Node{node.Val, make([]*Node, n)}
		clones[node.Val] = answer
		for i := 0; i < n; i++ {
			answer.Neighbors[i] = clone(clones, node.Neighbors[i])
		}
	}
	return answer
}

func cloneGraph(node *Node) *Node {
	if node == nil {
		return nil
	}
	clones := make(map[int]*Node)
	return clone(clones, node)
}

func Clone_graph() {
	a := Node{1, make([]*Node, 2)}
	b := Node{2, make([]*Node, 2)}
	c := Node{3, make([]*Node, 2)}
	d := Node{4, make([]*Node, 2)}
	a.Neighbors[0] = &b
	a.Neighbors[1] = &d
	b.Neighbors[0] = &a
	b.Neighbors[1] = &c
	c.Neighbors[0] = &b
	c.Neighbors[1] = &d
	d.Neighbors[0] = &a
	d.Neighbors[1] = &c
	result := cloneGraph(&a)
	one := result
	two := result.Neighbors[0]
	three := two.Neighbors[1]
	four := three.Neighbors[1]
	fmt.Println(one.Val)
	fmt.Println(two.Val)
	fmt.Println(three.Val)
	fmt.Println(four.Val)
}
