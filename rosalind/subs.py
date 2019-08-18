# http://rosalind.info/problems/subs/

import six

def subs(dna, motif):
  answers = []
  index = 0
  while True:
    index = dna.find(motif, index)
    if index == -1:
      break
    else:
      index = index + 1
      answers.append(index)
  return answers

def main():
  dna = six.moves.input()
  motif = six.moves.input()
  answers = subs(dna, motif)
  print(' '.join(str(a) for a in answers))

if __name__ == "__main__":
  main()
