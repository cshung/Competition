# http://rosalind.info/problems/scc/

from sys import stdin
from collections import deque

def scc(adj):
  n = len(adj)
  visited = [False] * n
  onstack = [False] * n
  indices = [None] * n
  low = [None] * n
  stack = []
  count = [0]
  index = [0]

  def dfs(i):
    stack.append(i)
    onstack[i] = True
    indices[i] = index[0]
    low[i] = index[0]
    index[0] += 1
    visited[i] = True
    for n in adj[i]:
      if not visited[n]:
        dfs(n)
        low[i] = min(low[i], low[n])
      elif onstack[n]:
        low[i] = min(low[i], indices[n])
    if low[i] == indices[i]:
      count[0] += 1
      while True:
        v = stack.pop()
        onstack[v] = False
        if v == i:
          break

  for i in range(n):
    if not visited[i]:
      dfs(i)

  return count[0]

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  tokens = data[0].split()
  n = int(tokens[0])
  m = int(tokens[1])
  adj = [[] for _ in range(n)]
  for i in range(m):
    tokens = data[i + 1].split()
    src = int(tokens[0]) - 1
    dst = int(tokens[1]) - 1
    adj[src].append(dst)
  answer = scc(adj)
  print(answer)

if __name__ == "__main__":
  main()
