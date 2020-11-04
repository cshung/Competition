# http://rosalind.info/problems/subs/

from sys import stdin

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
  data = []
  for line in stdin:
    data.append(line.strip())
  dna = data[0]
  motif = data[1]
  answers = subs(dna, motif)
  print(' '.join(str(a) for a in answers))

if __name__ == "__main__":
  main()
