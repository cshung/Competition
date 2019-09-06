# http://rosalind.info/problems/prob/

import six
import math

def prob(dna,probs):
  answers = []
  for p in probs:
    pgc = p / 2
    pat = (1 - p) / 2
    lgc = math.log10(pgc)
    lat = math.log10(pat)
    answer = 0
    for c in dna:
      if c == 'A' or c == 'T':
        answer = answer + lat
      else:
        answer = answer + lgc
    answers.append(answer)
  return answers

def main():
  dna = six.moves.input()
  line = six.moves.input()
  probs = [float(token) for token in line.split(' ')]
  answers = prob(dna, probs)
  print(' '.join(str(answer) for answer in answers))

if __name__ == "__main__":
  main()
