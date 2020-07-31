# http://rosalind.info/problems/pmch/

from sys import stdin
from libfasta import readFasta
import math

def pmch(rna):
  a = 0
  c = 0
  for n in rna:
    if n == 'A':
      a = a + 1
    elif n == 'C':
      c = c + 1
  return math.factorial(a) * math.factorial(c)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  answer = pmch(records[0][1])
  print(answer)

if __name__ == "__main__":
  main()
