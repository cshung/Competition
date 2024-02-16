# http://rosalind.info/problems/bip/

from sys import stdin
from collections import deque

def bip(adjs):
  answers = []
  for adj in adjs:
    v = len(adj)
    colors = [2] * v
    answer = 1
    for s in range(v):
      if colors[s] == 2:
        bfs = deque()
        bfs.append(s)
        colors[s] = 0
        while len(bfs) > 0:
          cur = bfs.popleft()
          for n in adj[cur]:
            if colors[n] == 2:
              bfs.append(n)
              colors[n] = 1 - colors[cur]
            else:
              if colors[n] != 1 - colors[cur]:
                answer = -1
                break
    answers.append(answer)
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
      adj[dst].append(src)
    adjs.append(adj)
  answers = bip(adjs)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
