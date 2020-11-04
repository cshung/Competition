# http://rosalind.info/problems/rna/

from sys import stdin

def rna(dna):
  return dna.replace("T","U")

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  dna = data[0]
  print(rna(dna))

if __name__ == "__main__":
  main()
