# http://rosalind.info/problems/gs/

from sys import stdin
from collections import deque

def gs(adjs):
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

    #
    # Step 2: Imagine all the nodes in the same SCC is contracted into a single node
    #         The result is a forest because we cannot have cycles between SCCs.
    #         The last SCC returned by Tarjan's is a root in one of the SCCs.
    #
    # If an arbitrary node in the last SCC can reach the whole graph, it is a general source
    # otherwise, no other node in any other SCCs can possibly reach it, so we can declare there
    # is none.
    #
    candidate = sccs[-1][0]
    n = len(adj)
    visited = [False] * n
    def reachable(i):
      answer = 1
      visited[i] = True
      for n in adj[i]:
        if not visited[n]:
          answer += reachable(n)
      return answer

    if reachable(candidate) == len(adj):
      smart = candidate + 1
    else:
      smart = -1

    answers.append(smart)
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
  answers = gs(adjs)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
