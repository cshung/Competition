# http://rosalind.info/problems/sset/

from sys import stdin

def sset(n):
  return modpower(2, n, 1000000)

def modpower(a,n,p):
  if n == 0:
    return 1
  elif n == 1:
    return a
  else:
    half = n // 2;
    h = modpower(a, half, p)
    if half * 2 < n:
      return h * h * a % p
    else:
      return h * h % p

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  line = data[0]
  print(sset(int(line)))

if __name__ == "__main__":
  main()
