# http://rosalind.info/problems/rear/

from sys import stdin
from collections import deque
from math import factorial
import datetime
from librear import parents
from libperm import encode
from libperm import decode

def reversal_distance(source, target):
  map = {}
  for canon in range(0, len(source)):
    map[source[canon] - 1] = canon
  mapped_target = []
  for v in target:
    mapped_target.append(map[v - 1])
  code = encode(mapped_target)
  distance = 0
  while code != 0:
    code = parents[code]
    distance = distance + 1
  return distance

def rear(data):
  n = len(data) // 2
  for i in range(0, n):
    print(reversal_distance(data[2 * i], data[2 * i + 1]))

def main():
  data = []
  for line in stdin:
    line = line.strip()
    if line != '':
      data.append([int(token) for token in line.split()])
      if len(data) == 2:
        print(reversal_distance(data[0], data[1]))
        data = []

if __name__ == "__main__":
  main()
