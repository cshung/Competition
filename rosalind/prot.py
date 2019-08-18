# http://rosalind.info/problems/prot/

import six
from libcode import code

def prot(rna):
  i = 0
  protein = ""
  while(True):
    if i + 2 < len(rna):
      key = rna[i] + rna[i + 1] + rna[i + 2]
      m = code[key]
      i = i + 3
      if m == "Stop":
        break
      else:
        protein = protein + m
    else:
      break
  return protein

def main():
  rna = six.moves.input()
  protein = prot(rna)
  print(protein)

if __name__ == "__main__":
  main()
