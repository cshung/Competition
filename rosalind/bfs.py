# http://rosalind.info/problems/bfs/

from sys import stdin
from collections import deque

def bfs(adj):
  answers = [-1] * len(adj)
  bfs = deque()
  enqueued = set()
  bfs.append((0, 0))
  enqueued.add(0)
  while len(bfs) > 0:
    (cur,dist) = bfs.popleft()
    answers[cur] = dist
    for n in adj[cur]:
      if n not in enqueued:
        bfs.append((n, dist + 1))
        enqueued.add(n)
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
  answers = bfs(adj)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
