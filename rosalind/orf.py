# http://rosalind.info/problems/orf/

from sys import stdin
from libfasta import readFasta

def indexes(text, pattern):
  answers = []
  index = 0
  while True:
    index = text.find(pattern, index)
    if index == -1:
      break
    else:
      index = index + 1
      answers.append(index)
  return answers

def orf(dna):
  rna = dna.replace("T","U")
  startCodonIndexes = indexes(rna, "AUG")
  for startCodonIndex in startCodonIndexes:
    print(startCodonIndex)
  

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  answers = orf(records[0][1])

if __name__ == "__main__":
  main()
