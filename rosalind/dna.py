# http://rosalind.info/problems/dna/

from sys import stdin

def dna(problem):
  a = 0
  c = 0
  g = 0
  t = 0
  for n in problem:
    if n == 'A':
      a = a + 1
    elif n == 'C':
      c = c + 1
    elif n == 'G':
      g = g + 1
    elif n == 'T':
      t = t + 1
  return (a,c,g,t)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  problem = data[0]
  (a,c,g,t) = dna(problem)
  print("%d %d %d %d" % (a,c,g,t))

if __name__ == "__main__":
  main()
