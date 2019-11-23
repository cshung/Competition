# http://rosalind.info/problems/tran/

from sys import stdin
from libfasta import readFasta

def tran(records):
    (_, dna1) = records[0]
    (_, dna2) = records[1]
    length = len(dna1)
    partner = {}
    partner['A'] = 'G'
    partner['C'] = 'T'
    partner['T'] = 'C'
    partner['G'] = 'A'
    transition = 0.0
    transversions = 0.0
    for i in range(0, length):
        n1 = dna1[i]
        n2 = dna2[i]
        if n1 == n2:
            pass
        elif n1 == partner[n2]:
            transition = transition + 1
        else:
            transversions = transversions + 1
    return transition /transversions
    

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  print(tran(records))

if __name__ == "__main__":
  main()
