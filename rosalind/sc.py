# http://rosalind.info/problems/sc/

from sys import stdin
from collections import deque

def sc(adjs):
  answers = []
  for adj in adjs:
    #
    # Step 1: Form a DAG of the strongly connected components
    #
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

    #
    # Step 3: Check if the SCC graph is hamiltonian
    #
    valid = True
    for i in range(n - 1):
      s = topo[i]
      d = topo[i + 1]
      if d not in scc_graph[s]:
        valid = False
        break
    if valid:
      answers.append(1)
    else:
      answers.append(-1)

  return answers

def main():
  data = []
  for line in stdin:
    line = line.strip()
    if len(line) > 0:
      data.append(line)
  adjs = []
  l = 0
  tokens = data[0].split()
  l += 1
  c = int(tokens[0])
  for _ in range(c):
    tokens = data[l].split()
    l += 1
    n = int(tokens[0])
    m = int(tokens[1])
    adj = [[] for _ in range(n)]
    for i in range(m):
      tokens = data[l].split()
      l += 1
      src = int(tokens[0]) - 1
      dst = int(tokens[1]) - 1
      adj[src].append(dst)
    adjs.append(adj)
  answers = sc(adjs)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
