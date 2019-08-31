# http://rosalind.info/problems/prtm/

import six
from libcode import mass

def prtm(protein):
  answer = 0
  for residue in protein:
    answer = answer + mass[residue]
  return answer
  
def main():
  protein = six.moves.input()
  print(prtm(protein))

if __name__ == "__main__":
  main()
