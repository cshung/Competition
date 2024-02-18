# http://rosalind.info/problems/nwc/

from sys import stdin

def nwc(adjs):
  answers = []
  for adj in adjs:
    n = len(adj)
    visited = [False] * n
    cc = []
    ccs = []

    def dfs(i):
      cc.append(i)
      visited[i] = True
      for (neighbor, _) in adj[i]:
        if not visited[neighbor]:
          dfs(neighbor)

    for i in range(n):
      if not visited[i]:
        dfs(i)
        ccs.append(cc)
        cc = []

    found = False
    for cc in ccs:
      if len(cc) > 1:
        dists = ['x'] * n
        dists[cc[0]] = 0
        for round in range(n):
          new_dists = list(dists)
          for node in cc:
            if dists[node] != 'x':
              for (dst, w) in adj[node]:
                candidate = dists[node] + w
                if new_dists[dst] == 'x' or new_dists[dst] > candidate:
                  new_dists[dst] = candidate
                  if round == n - 1:
                    found = True
          dists = new_dists
      if found:
        break
    if found:
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
      dist = int(tokens[2])
      adj[src].append((dst, dist))
    adjs.append(adj)
  answers = nwc(adjs)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
