# http://rosalind.info/problems/splc/

from sys import stdin
from libfasta import readFasta
from prot import prot
from rna import rna

def splc(records):
  dna = records[0][1]
  while True:
    cut = False
    for i in range(1, len(records)):
      intron = records[i][1]
      index = dna.find(intron)
      if index != -1:
        dna = dna[:index] + dna[index + len(intron):]
        cut = True
        break
    if not cut:
      break
  mrna = rna(dna)
  return prot(mrna)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  answer = splc(records)
  print(answer)

if __name__ == "__main__":
  main()
