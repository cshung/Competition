# http://rosalind.info/problems/bins/

from sys import stdin
from bisect import bisect_left

def bins(arr, keys):
  answers = []
  for key in keys:
    index = bisect_left(arr, key)
    if arr[index] == key:
      answer = index + 1
    else:
      answer = -1
    answers.append(answer)
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  arr = [int(x) for x in data[2].split()]
  keys = [int(x) for x in data[3].split()]
  answers = bins(arr, keys)
  print(" ".join([str(x) for x in answers]))

if __name__ == "__main__":
  main()
