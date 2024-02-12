# http://rosalind.info/problems/conv/

from sys import stdin

def conv(s1, s2):
  s = {} 
  f = 1
  for a in s1:
    for b in s2:
      d = round(a * 100000) - round(b * 100000)
      if d not in s:
        s[d] = 0
      s[d] += 1
      if s[d] > f:
        f = s[d]
  check = 0
  for k in s:
    if s[k] == f:
      return (k/100000, s[k])

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  s1 = [float(x) for x in data[0].split()]
  s2 = [float(x) for x in data[1].split()]
  (d,f) = conv(s1, s2)
  print(f)
  print(d)

if __name__ == "__main__":
  main()
