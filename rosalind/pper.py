# http://rosalind.info/problems/pper/

import six
import math

def pper(n,k):
  return math.factorial(n)/math.factorial(n-k) % 1000000

def main():
  line = six.moves.input()
  tokens = line.split(' ')
  n = int(tokens[0])
  k = int(tokens[1])
  answer = pper(n,k)
  print("%d" % answer)

if __name__ == "__main__":
  main()
