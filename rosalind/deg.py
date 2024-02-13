# http://rosalind.info/problems/deg/

from sys import stdin

def deg(adj):
  return [len(l) for l in adj]

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
  answers = deg(adj)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
