# http://rosalind.info/problems/sdag/

from sys import stdin
from collections import deque

def sdag(adj):
  n = len(adj)
  visited = [False] * n
  count = 0
  topo = []

  def dfs(i):
    visited[i] = True
    for (n, _) in adj[i]:
      if not visited[n]:
        dfs(n)
    topo.append(i)

  for i in range(n):
    if not visited[i]:
      count += 1
      dfs(i)

  topo.reverse()
  dists = ['x'] * n
  dists[0] = 0
  parents = ['x'] * n

  rev = [[] for _ in range(n)]
  for src in range(n):
    for (dst, w) in adj[src]:
      rev[dst].append((src, w))

  for t in topo:
    for (p, w) in rev[t]:
      if dists[p] != 'x':
        candidate = dists[p] + w
        if dists[t] == 'x' or dists[t] > candidate:
          parents[t] = p
          dists[t] = candidate

  return dists

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  tokens = data[0].split()
  n = int(tokens[0])
  m = int(tokens[1])
  adj = [[] for _ in range(n)]
  dup = [set() for _ in range(n)]
  for i in range(m):
    tokens = data[i + 1].split()
    src = int(tokens[0]) - 1
    dst = int(tokens[1]) - 1
    dist = int(tokens[2]) 
    if dst not in dup[src]:
      # There is an implict requirement that if multiple edges exists
      # we must take the first one in the input. This is just wrong.
      adj[src].append((dst, dist))
      dup[src].add(dst)
  for i in range(n):
    edges = adj[i]
    s = [x for (x, y) in edges]
    if (len(s) != len(set(s))):
      print(edges)
  answers = sdag(adj)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
