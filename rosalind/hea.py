# http://rosalind.info/problems/hea/

from sys import stdin
from heapq import heapify

def hea(problem):
  negative = [-x for x in problem]
  heapify(negative)
  return [-x for x in negative]

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answers = hea([int(x) for x in data[1].split()])
  print(" ".join([str(x) for x in answers]))

if __name__ == "__main__":
  main()
