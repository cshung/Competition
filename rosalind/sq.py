# http://rosalind.info/problems/sq/

from sys import stdin

def sq(matrices):
  answers = []
  for matrix in matrices:
    n = len(matrix)
    found = False
    for p in range(n):
      for q in range(n):
        s = 0
        for r in range(n):
          s += matrix[p][r] * matrix[r][q]
        if s > 1 and p != q:
          found = True
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
      data.append(line.strip())
  l = 0
  g = int(data[l].split()[0])
  l += 1
  matrices = []
  for _ in range(g):
    line = data[l]
    l += 1
    tokens = line.split()
    n = int(tokens[0])
    m = int(tokens[1])
    matrix = [[0 for _ in range(n)] for _ in range(n)]
    for _ in range(m):
      edge = data[l]
      l += 1
      tokens = edge.split()
      src = int(tokens[0]) - 1
      dst = int(tokens[1]) - 1
      matrix[src][dst] = 1
      matrix[dst][src] = 1
    matrices.append(matrix)
  answers = sq(matrices)
  print(" ".join([str(x) for x in answers]))

if __name__ == "__main__":
  main()
