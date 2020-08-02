# http://rosalind.info/problems/rear/

from sys import stdin
from collections import deque

def num(l, i):
  if i == len(l):
    return 0
  else:
    return l[i] + 10 * num(l, i + 1)

def prepare():
  n = 10
  graph = {}
  prepare_worker(list(range(0, n)), 0, graph)
  return graph

last_progress = 0

def prepare_worker(l, i, graph):
  n = len(l)
  if i == n:
    neighbors = []
    graph[num(l, 0)]=neighbors
    global last_progress
    progress = len(graph) * 100 // 3628800
    if progress != last_progress:
      print(progress)
      last_progress = progress
    for i in range(0, n):
      for j in range(i + 1, n):
        left = i
        right = j 
        while left < right:
          temp = l[left]
          l[left] = l[right]
          l[right] = temp
          left = left + 1
          right = right - 1
        neighbors.append(num(l, 0))
        left = i
        right = j 
        while left < right:
          temp = l[left]
          l[left] = l[right]
          l[right] = temp
          left = left + 1
          right = right - 1
  else:
    for j in range(i, len(l)):
      temp = l[i]
      l[i] = l[j]
      l[j] = temp
      prepare_worker(l, i + 1, graph)
      temp = l[i]
      l[i] = l[j]
      l[j] = temp

def reversal_distance(source, target, graph):
  if source == target:
    return 0
  source_number = num([int(i) - 1 for i in source.split(" ")], 0)
  target_number = num([int(i) - 1 for i in target.split(" ")], 0)
  queue = deque()
  enqueued = {}
  queue.append((0, source_number))
  enqueued[source_number] = True
  while len(queue) > 0:
    (distance, visiting) = queue.popleft()
    for neighbor in graph[visiting]:
      if visiting == target_number:
        return distance + 1
      else:
        queue.append((distance + 1, neighbor))

def rear(data):
  n = len(data) // 2
  for i in range(0, n):
    print(reversal_distance(data[2 * i], data[2 * i + 1], graph))

def main():
  graph = prepare()
  data = []
  for line in stdin:
    line = line.strip()
    if line != '':
      data.append(line)
  print(rear(data))

if __name__ == "__main__":
  main()
