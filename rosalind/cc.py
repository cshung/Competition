# http://rosalind.info/problems/cc/

from sys import stdin
from collections import deque

def cc(adj):
  n = len(adj)
  visited = [False] * n
  count = 0

  def dfs(i):
    visited[i] = True
    for n in adj[i]:
      if not visited[n]:
        dfs(n)

  for i in range(n):
    if not visited[i]:
      count += 1
      dfs(i)

  return count

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
    adj[dst].append(src)
  answer = cc(adj)
  print(answer)

if __name__ == "__main__":
  main()
