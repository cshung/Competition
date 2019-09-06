# http://rosalind.info/problems/sset/

import six

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
  line = six.moves.input()
  print(sset(int(line)))

if __name__ == "__main__":
  main()
