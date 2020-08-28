# http://rosalind.info/problems/rear/

from sys import stdin
from collections import deque
from math import factorial
import datetime
from librear import parents
from libperm import encode
from libperm import decode

def reversal_distance(target, source):
  map = {}
  for canon in range(0, len(source)):
    map[source[canon] - 1] = canon
  mapped_target = []
  for v in target:
    mapped_target.append(map[v - 1])
  code = encode(mapped_target)
  distance = 0
  path = []
  while code != 0:
    before = decode(code, 10)
    code = parents[code]
    after = decode(code, 10)
    first = 0
    last = 9
    while before[first] == after[first]:
      first = first + 1
    while before[last] == after[last]:
      last = last - 1
    path.append((first + 1, last + 1))
    distance = distance + 1
  return (distance, path)

def sort(data):
  (distance, path) = reversal_distance(data[0], data[1])
  print(distance)
  for element in path:
    print("%s %s" % element)

def main():
  data = []
  for line in stdin:
    line = line.strip()
    if line != '':
      data.append([int(token) for token in line.split()])
  sort(data)

if __name__ == "__main__":
  main()
