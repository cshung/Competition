# http://rosalind.info/problems/hs/

from sys import stdin
from heapq import heapify, heappop

def hs(array):
  heapify(array)
  answer = []
  while len(array) > 0:
    answer.append(heappop(array))
  return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answers = hs([int(x) for x in data[1].split()])
  print(" ".join([str(x) for x in answers]))

if __name__ == "__main__":
  main()
