import sys
import datetime
from collections import deque
from math import factorial
from libperm import encode
from libperm import decode

def eprint(*args, **kwargs):
  print(*args, file=sys.stderr, **kwargs)

def main():
  last_progress = 0
  n = 10
  done = factorial(n)
  root = list(range(0, n))
  bfs_parent = deque()
  bfs_perm = deque()
  parents = {}
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
        if neighbor_key not in parents:
          bfs_perm.append(neighbor_key)
          bfs_parent.append(key)
          parents[neighbor_key] = key
          progress = len(parents) * 100 // done
          if progress != last_progress:
            eprint(progress)
            last_progress = progress
          if (len(parents) == done):
            break
        left = i
        right = j 
        while left < right:
          temp = perm[left]
          perm[left] = perm[right]
          perm[right] = temp
          left = left + 1
          right = right - 1
  print("parents = [0] * %s" % len(parents))
  for key in parents:
    print("parents[%s] = %s" % (key, parents[key]))

if __name__ == "__main__":
  main()
