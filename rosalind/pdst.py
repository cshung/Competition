# http://rosalind.info/problems/pdst/

from sys import stdin
from libfasta import readFasta

def pdst(records):
  n = len(records)
  l = len(records[0][1])
  matrix = []  
  for i in range(0, n):
    matrix.append([0] * n)
  for i in range(0, n):
    for j in range(1, n):
      (_, dna_i) = records[i]
      (_, dna_j) = records[j]
      mismatch = 0
      for k in range(0, l):
        if dna_i[k] != dna_j[k]:
          mismatch = mismatch + 1
      matrix[i][j] = matrix[j][i] = mismatch / l
  return matrix

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  answer = pdst(records)
  for row in answer:
    print(" ".join([("%.4f" % i) for i in row]))

if __name__ == "__main__":
  main()
