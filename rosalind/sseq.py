# http://rosalind.info/problems/sseq/

from sys import stdin
from libfasta import readFasta

def sseq(records):
  dna1 = records[0][1]
  dna2 = records[1][1]
  i = 0
  j = 0
  check = ""
  indexes = []
  while j < len(dna2):
      while dna1[i] != dna2[j]:
        i = i + 1
      indexes.append(i)
      i = i + 1
      j = j + 1
  return indexes

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  indexes = sseq(records)
  print(' '.join(str(index + 1) for index in indexes))

if __name__ == "__main__":
  main()
