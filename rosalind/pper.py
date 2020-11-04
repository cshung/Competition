# http://rosalind.info/problems/pper/

from sys import stdin
import math

def pper(n,k):
  return math.factorial(n)/math.factorial(n-k) % 1000000

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  line = data[0]
  tokens = line.split(' ')
  n = int(tokens[0])
  k = int(tokens[1])
  answer = pper(n,k)
  print("%d" % answer)

if __name__ == "__main__":
  main()
