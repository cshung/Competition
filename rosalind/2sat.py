# http://rosalind.info/problems/2sat/

from sys import stdin, setrecursionlimit

setrecursionlimit(1500)

def twosat(problems):
  def forward(v):
    if v > 0:
      return 2 * (v - 1)
    else:
      return -2 * v - 1
  def backward(i):
    if i % 2 == 0:
      return i // 2 + 1
    else:
      return (i + 1) // (-2)

  answers = []
  for (num_variables, clauses) in problems:
    adj = [[] for _ in range(2 * num_variables)]
    for (alpha, beta) in clauses:
      src1 = forward(-alpha)
      dst1 = forward(beta)
      src2 = forward(-beta)
      dst2 = forward(alpha)
      adj[src1].append(dst1)
      adj[src2].append(dst2)
    
    n = len(adj)
    visited = [False] * n
    onstack = [False] * n
    indices = [None] * n
    low = [None] * n
    stack = []
    index = [0]
    node_scc = [None] * n
    sccs = []

    def compute_scc(i):
      stack.append(i)
      onstack[i] = True
      indices[i] = index[0]
      low[i] = index[0]
      index[0] += 1
      visited[i] = True
      for n in adj[i]:
        if not visited[n]:
          compute_scc(n)
          low[i] = min(low[i], low[n])
        elif onstack[n]:
          low[i] = min(low[i], indices[n])
      if low[i] == indices[i]:
        scc_index = len(sccs)
        scc = []
        while True:
          v = stack.pop()
          scc.append(v)
          node_scc[v] = scc_index
          onstack[v] = False
          if v == i:
            break
        sccs.append(scc)

    for i in range(n):
      if not visited[i]:
        compute_scc(i)

    scc_graph = [set() for _ in sccs]
    for src in range(len(adj)):
      for dst in adj[src]:
        s = node_scc[src]
        d = node_scc[dst]
        if s != d:
          scc_graph[s].add(d)
    #
    # Step 2: Compute the topological order of the scc_graph
    #
    n = len(scc_graph)
    visited = [False] * n
    topo = []

    def compute_topo(i):
      visited[i] = True
      for n in scc_graph[i]:
        if not visited[n]:
          compute_topo(n)
      topo.append(i)

    for i in range(n):
      if not visited[i]:
        compute_topo(i)
    topo.reverse()

    valid = True
    assignment = [0] * num_variables
    for t in topo:
      current_assignment = [0] * num_variables
      for n in sccs[t]:
        sv = backward(n)
        v = abs(sv)
        if assignment[v - 1] == 0:
          if current_assignment[v - 1] == 0:
            current_assignment[v - 1] = -sv
          else:
            valid = False
      if valid:
        for i in range(len(current_assignment)):
          if current_assignment[i] != 0:
            assignment[i] = current_assignment[i]
    if valid:
      answers.append([1] + list(assignment))
    else:
      answers.append([0])
  return answers

def main():
  data = []
  for line in stdin:
    line = line.strip()
    if len(line) > 0:
      data.append(line)
  l = 0
  c = int(data[l].split()[0])
  l += 1
  problems = []
  for _ in range(c):
    tokens = data[l].split()
    l += 1
    num_variables = int(tokens[0])
    num_clauses = int(tokens[1])
    clauses = []
    for _ in range(num_clauses):
      tokens = data[l].split()
      l += 1
      alpha = int(tokens[0])
      beta = int(tokens[1])
      clauses.append((alpha, beta))
    problems.append((num_variables, clauses))
  answers = twosat(problems)
  for row in answers:
    print(" ".join([str(x) for x in row]))

if __name__ == "__main__":
  main()
