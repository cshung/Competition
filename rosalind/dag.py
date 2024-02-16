# http://rosalind.info/problems/dag/

from sys import stdin

def dag(adjs):
  answers = []
  for adj in adjs:
    n = len(adj)
    colors = [0] * n

    def dfs(i):
      colors[i] = 1
      for n in adj[i]:
        if colors[n] == 0:
          if not dfs(n):
            return False
        elif colors[n] == 1:
          return False
      colors[i] = 2
      return True

    answer = 1
    for i in range(n):
      if colors[i] == 0:
        if not dfs(i):
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
    adjs.append(adj)
  answers = dag(adjs)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
