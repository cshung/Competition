# http://rosalind.info/problems/edit/

from sys import stdin
from libfasta import readFasta
from liblevenshtein import levenshtein

def edit(str1, str2):
  m = len(str1)
  n = len(str2)
  (cost, choice) = levenshtein(str1, str2, True)
  return cost[m][n]

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  ans = edit(records[0][1], records[1][1])
  print(ans)

if __name__ == "__main__":
  main()
