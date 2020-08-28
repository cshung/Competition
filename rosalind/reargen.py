import sys
from collections import deque
from math import factorial
from libperm import encode
from libperm import decode

def eprint(*args, **kwargs):
  print(*args, file=sys.stderr, **kwargs)

def main():
  progress = 0
  last_progress_percent = 0
  n = 10
  root = list(range(0, n))
  bfs_parent = deque()
  bfs_perm = deque()
  parents = [None] * factorial(n)
  bfs_parent.append(None)
  bfs_perm.append(encode(root))
  parents[encode(root)] = 0
  while len(bfs_perm) > 0:
    key = bfs_perm.popleft()
    perm = decode(key, n)
    parent = bfs_parent.popleft()
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
        neighbor_key = encode(perm)
        if parents[neighbor_key] == None:
          bfs_perm.append(neighbor_key)
          bfs_parent.append(key)
          parents[neighbor_key] = key
          progress = progress + 1
          progress_percent = progress * 100 // len(parents)
          if progress_percent != last_progress_percent:
            eprint(progress_percent)
            last_progress_percent = progress_percent
        left = i
        right = j 
        while left < right:
          temp = perm[left]
          perm[left] = perm[right]
          perm[right] = temp
          left = left + 1
          right = right - 1
    if progress == len(parents):
      break
  print("parents = %s" % parents)

if __name__ == "__main__":
  main()
