# http://rosalind.info/problems/grph/

from sys import stdin
from libfasta import readFasta

def grph(records):
  answers = []
  for (label1, dna1) in records:
    for (label2, dna2) in records:
      if len(dna1) >= 3 and len(dna2) >= 3 and dna1 != dna2 and dna1[len(dna1) - 3: len(dna1)] == dna2[0:3]:
        answers.append((label1, label2))
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  answers = grph(records)
  for (label1, label2) in answers:
    print("%s %s" % (label1, label2))

if __name__ == "__main__":
  main()
