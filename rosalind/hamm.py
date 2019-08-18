# http://rosalind.info/problems/hamm/

import six

def hamm(dna1, dna2):
  answer = 0
  for i in range(0, len(dna1)):
    if not dna1[i] == dna2[i]:
      answer = answer + 1
  return answer

def main():
  dna1 = six.moves.input()
  dna2 = six.moves.input()
  answer = hamm(dna1, dna2)
  print(answer)

if __name__ == "__main__":
  main()
