# http://rosalind.info/problems/inod/

from sys import stdin

def inod(n):
  return n - 2

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answer = inod(int(data[0]))
  print(answer)

if __name__ == "__main__":
  main()
