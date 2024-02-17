# http://rosalind.info/problems/bf/

from sys import stdin

def bf(adj):
  n = len(adj)
  dists = ['x'] * n
  dists[0] = 0
  for round in range(n - 1):
    new_dists = list(dists)
    for node in range(n):
      if dists[node] != 'x':
        for (dst, w) in adj[node]:
          candidate = dists[node] + w
          if new_dists[dst] == 'x' or new_dists[dst] > candidate:
            new_dists[dst] = candidate
    dists = new_dists
  return dists

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
    dist = int(tokens[2])
    adj[src].append((dst, dist))
  answers = bf(adj)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
