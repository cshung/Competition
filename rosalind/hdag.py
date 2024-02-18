# http://rosalind.info/problems/hdag/

from sys import stdin

def hdag(adjs):
  answers = []
  for adj in adjs:
    n = len(adj)
    visited = [False] * n
    count = 0
    topo = []

    def dfs(i):
      visited[i] = True
      for n in adj[i]:
        if not visited[n]:
          dfs(n)
      topo.append(i + 1)

    for i in range(n):
      if not visited[i]:
        count += 1
        dfs(i)

    topo.append(1)
    topo.reverse()
    valid = True
    for i in range(n - 1):
      src = topo[i + 1] - 1
      dst = topo[i + 2] - 1
      if dst not in adj[src]:
        valid = False
        break
    if valid:
      answers.append(topo)
    else:
      answers.append([-1])
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
  answers = hdag(adjs)
  for row in answers:
    print(" ".join(str(x) for x in row))

if __name__ == "__main__":
  main()
