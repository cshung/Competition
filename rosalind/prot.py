# http://rosalind.info/problems/prot/

from sys import stdin
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
  data = []
  for line in stdin:
    data.append(line.strip())
  rna = data[0]
  protein = prot(rna)
  print(protein)

if __name__ == "__main__":
  main()
