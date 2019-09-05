# http://rosalind.info/problems/long/

from sys import stdin
from libfasta import readFasta
from libkmp import build_kmp_shift, kmp_overlap

def long(records):
  num_records = len(records)
  shifts = [None] * num_records
  matrix = [[0 for i in range(num_records)] for j in range(num_records)] 
  for i in range(0, num_records):
    dna = records[i][1]
    shifts[i] = build_kmp_shift(dna)
  for i in range(0, num_records):
    for j in range(0, num_records):
      if i != j:
        dna1 = records[i][1]
        dna2 = records[j][1]
        overlap = kmp_overlap(dna1, dna2, shifts[j])
        if overlap > len(dna)//2 or overlap > len(dna2) // 2:
          matrix[i][j] = overlap
          if False:
            offset = len(dna1) - overlap
            print(overlap)
            print(dna1)
            print(' ' * offset + dna2)
  order = topo(matrix)
  s = ""
  for i in range(0, num_records):
    if i == 0:
      s = records[order[i]][1]
    else:
      p = order[i - 1]
      q = order[i]
      overlap = matrix[p][q]
      s = s + (records[q][1][overlap:])
  print(s)

def topo(matrix):
  visited = [0] * len(matrix)
  order = []
  for i in range(0, len(matrix)):
    if visited[i] == 0:
      dfs(i, matrix, visited, order)
  order.reverse()
  return order

def dfs(i, matrix, visited, order):
  visited[i] = 1
  for j in range(0, len(matrix)):
    if matrix[i][j] != 0 and visited[j] == 0:
      dfs(j, matrix, visited, order)
  visited[i] = 2
  order.append(i)
  

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  long(records)

if __name__ == "__main__":
  main()
