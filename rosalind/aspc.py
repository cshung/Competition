# http://rosalind.info/problems/aspc/

from sys import stdin
from math import comb

def aspc(n,m):
  sum = 0
  for k in range(m, n+1):
    sum += comb(n, k)
    sum %= 1000000
  return sum

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  line = data[0]
  tokens = line.split(' ')
  n = int(tokens[0])
  m = int(tokens[1])
  answer = aspc(n,m)
  print("%d" % answer)

if __name__ == "__main__":
  main()
