# http://rosalind.info/problems/ts/

from sys import stdin
from collections import deque

def ts(adj):
  n = len(adj)
  visited = [False] * n
  count = 0
  answers = []

  def dfs(i):
    visited[i] = True
    for n in adj[i]:
      if not visited[n]:
        dfs(n)
    answers.append(i + 1)

  for i in range(n):
    if not visited[i]:
      count += 1
      dfs(i)

  answers.reverse()
  return answers

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
  answers = ts(adj)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
