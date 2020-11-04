# http://rosalind.info/problems/iprb/

from sys import stdin

def iprb(k,m,n):
  N = k + m + n
  C = N * (N - 1) * 4.0
  R = n * (n - 1) * 4 + (m * n * 2) * 2 + (m * (m - 1)) * 1
  return (1 - R/C)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  line = data[0]
  tokens = line.split(' ')
  k = int(tokens[0])
  m = int(tokens[1])
  n = int(tokens[2])
  answer = iprb(k,m,n)
  print(answer)

if __name__ == "__main__":
  main()
