# http://rosalind.info/problems/prtm/

from sys import stdin
from libcode import mass

def prtm(protein):
  answer = 0
  for residue in protein:
    answer = answer + mass[residue]
  return answer
  
def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  protein = data[0]
  print(prtm(protein))

if __name__ == "__main__":
  main()
