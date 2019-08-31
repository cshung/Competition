# http://rosalind.info/problems/tree/

from sys import stdin

def tree(data):
  n = int(data[0])
  return n - len(data)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answer = tree(data)
  print(answer)

if __name__ == "__main__":
  main()
