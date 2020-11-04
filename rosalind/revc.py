# http://rosalind.info/problems/revc/

from sys import stdin

def complement(n):
  if n == 'A':
    return 'T'
  elif n == 'C':
    return 'G'
  elif n == 'G':
    return 'C'
  elif n == 'T':
    return 'A'

def revc(dna):
  nt = len(dna)
  answer = ""
  for i in range(0, nt):
    j = nt - 1 - i
    answer += complement(dna[j])
  return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  dna = data[0]
  answer = revc(dna)
  print(answer)

if __name__ == "__main__":
  main()

