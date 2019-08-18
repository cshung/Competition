# http://rosalind.info/problems/revc/

import six

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
  dna = six.moves.input()
  answer = revc(dna)
  print(answer)

if __name__ == "__main__":
  main()

