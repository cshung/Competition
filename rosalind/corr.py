# http://rosalind.info/problems/corr/

from sys import stdin
from revc import revc
from libbktree import bktree
from libfasta import readFasta
from hamm import hamm

def corr(records):
  dict = {}  
  for record in records:
    dna = record[1]
    rev = revc(dna)
    if dna in dict:
      dict[dna] = dict[dna] + 1
    else:
      dict[dna] = 1
    if rev in dict:
      dict[rev] = dict[rev] + 1
    else:
      dict[rev] = 1
  corrects = {}
  errors = []
  for record in records:
    dna = record[1]
    rev = revc(dna)
    if dna == rev:
      req = 3
    else:
      req = 2
    if dict[dna] < req:
      errors.append(dna)
    else:
      corrects[dna] = True
      corrects[rev] = True
  tree = bktree(hamm)
  for correct in corrects:
    tree.insert(correct)
  corrections = []
  for error in errors:
    substitutes = tree.query(error, 1)
    if len(substitutes) != 1:
      raise ValueError()
    correction="%s->%s" % (error,substitutes[0])
    corrections.append(correction)
  return corrections

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  for correction in corr(records):
    print(correction)

if __name__ == "__main__":
  main()
