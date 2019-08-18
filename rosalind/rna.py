# http://rosalind.info/problems/rna/

import six

def rna(dna):
  return dna.replace("T","U")

def main():
  dna = six.moves.input()
  print(rna(dna))

if __name__ == "__main__":
  main()
