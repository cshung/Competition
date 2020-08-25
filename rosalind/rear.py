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
    return code

def decode(perm):
    code = list(perm)
    for k in range(0, len(code)):
        i = len(code) - k - 1
        count = 0
        for j in range(i + 1, len(code)):
            if code[i] > code[j]:
                count = count + 1
            else:
                code[j] = code[j] + 1
    return code    

def to_number(code):
    answer = 0
    for i in range(0, len(code)):
        answer = answer + factorial(i) * code[len(code) - i - 1]
    return answer

def from_number(n, length):
    code = [0] * length
    for i in range(0, length):
        remainder = n % (i + 1)
        code[len(code) - 1 - i] = remainder
        n = n // (i + 1)
    return code

def prepare():
  print (datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
  last_progress = 0
  n = 10
  done = factorial(n)
  root = list(range(1, n + 1))
  bfs_perm = deque()
  bfs_dist = deque()
  distances = {}
  bfs_perm.append(root)
  bfs_dist.append(0)
  distances[str(root)] = 0
  while len(bfs_perm) > 0:
    perm = bfs_perm.popleft()
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
        key = str(perm)
        if key not in distances:
          bfs_perm.append(list(perm))
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
    map[source[canon]] = canon + 1
  mapped_target = []
  for v in target:
    mapped_target.append(map[v])
  return answers[str(mapped_target)]

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
