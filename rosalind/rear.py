# http://rosalind.info/problems/rear/

from sys import stdin
from collections import deque
from math import factorial
import datetime

def encode(perm):
  code = list(perm)
  for i in range(0, len(code)):
    count = 0
    for j in range(i + 1, len(code)):
      if code[i] > code[j]:
        count = count + 1
      else:
        code[j] = code[j] - 1
  answer = 0
  for i in range(0, len(code)):
    answer = answer + factorial(i) * code[len(code) - i - 1]
  return answer

def decode(n, length):
  perm = [0] * length
  for i in range(0, length):
    remainder = n % (i + 1)
    perm[length - 1 - i] = remainder
    n = n // (i + 1)
  for k in range(0, len(perm)):
    i = len(perm) - k - 1
    count = 0
    for j in range(i + 1, len(perm)):
      if perm[i] > perm[j]:
        count = count + 1
      else:
        perm[j] = perm[j] + 1
  return perm

def prepare():
  print (datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
  last_progress = 0
  n = 5
  done = factorial(n)
  root = list(range(0, n))
  bfs_perm = deque()
  bfs_dist = deque()
  distances = {}
  bfs_perm.append(encode(root))
  bfs_dist.append(0)
  distances[encode(root)] = 0
  while len(bfs_perm) > 0:
    perm = decode(bfs_perm.popleft(), n)
    dist = bfs_dist.popleft()
    for i in range(0, n):
      for j in range(i + 1, n):
        left = i
        right = j 
        while left < right:
          temp = perm[left]
          perm[left] = perm[right]
          perm[right] = temp
          left = left + 1
          right = right - 1
        key = encode(perm)
        if key not in distances:
          bfs_perm.append(key)
          bfs_dist.append(dist + 1)
          distances[key] = dist + 1
          progress = len(distances) * 100 // done
          if progress != last_progress:
            print(progress)
            last_progress = progress
          if (len(distances) == done):
            break
        left = i
        right = j 
        while left < right:
          temp = perm[left]
          perm[left] = perm[right]
          perm[right] = temp
          left = left + 1
          right = right - 1
  print (datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
  return distances

def reversal_distance(source, target, answers):
  map = {}
  for canon in range(0, len(source)):
    map[source[canon] - 1] = canon
  mapped_target = []
  for v in target:
    mapped_target.append(map[v - 1])
  return answers[encode(mapped_target)]

def rear(data, answers):
  n = len(data) // 2
  for i in range(0, n):
    print(reversal_distance(data[2 * i], data[2 * i + 1], answers))

def main():
  answers = prepare()
  data = []
  for line in stdin:
    line = line.strip()
    if line != '':
      data.append([int(token) for token in line.split()])
      if len(data) == 2:
        print(reversal_distance(data[0], data[1], answers))
        data = []

if __name__ == "__main__":
  main()
