# http://rosalind.info/problems/rstr/

from sys import stdin

def rstr(n, gc, dna):
  pa = (1 - gc)/2
  pc = gc/2
  p = 1
  for b in dna:
    if b == 'A':
      p = p * pa
    elif b == 'C':
      p = p * pc
    elif b == 'T':
      p = p * pa
    else:
      p = p * pc
  return 1 - (1 - p) ** n

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  tokens = data[0].split(' ')
  n = int(tokens[0])
  gc = float(tokens[1])
  dna = data[1]
  print(rstr(n, gc, dna))

if __name__ == "__main__":
  main()
