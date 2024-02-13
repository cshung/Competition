# http://rosalind.info/problems/ddeg/

from sys import stdin

def ddeg(adj):
  answers = []
  for l in adj:
    s = 0
    for n in l:
      s += len(adj[n])
    answers.append(s)
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
    adj[dst].append(src)
  answers = ddeg(adj)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
