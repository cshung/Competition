# http://rosalind.info/problems/ps/

from sys import stdin
from heapq import heapify, heappop

def ps(array, k):
  heapify(array)
  answers = []
  for i in range(k):
    answers.append(heappop(array))
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answers = ps([int(x) for x in data[1].split()], int(data[2]))
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
