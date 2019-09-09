# http://rosalind.info/problems/edta/

from sys import stdin
from libfasta import readFasta
from liblevenshtein import levenshtein

def edta(str1, str2):
  m = len(str1)
  n = len(str2)
  (cost, choice) = levenshtein(str1, str2, True)
  #
  # Using the choice array we built, backtrack to find the longest common subsequence
  #
  i = m
  j = n
  align1 = []
  align2 = []
  while i != 0 and j != 0:
    c = choice[i][j]
    if c == 0:
      i = i - 1
      j = j - 1
      if str1[i] != str2[j]:
        raise ValueError()
      align1.append(str1[i])
      align2.append(str2[j])
    elif c == 1:
      i = i - 1
      align1.append(str1[i])
      align2.append('-')
    elif c == 2:
      j = j - 1
      align2.append(str2[j])
      align1.append('-')
    elif c == 3:
      i = i - 1
      j = j - 1
      if str1[i] == str2[j]:
        raise ValueError()
      align1.append(str1[i])
      align2.append(str2[j])
    else:
      raise ValueError()
  align1.reverse()
  align2.reverse()
  return (cost[m][n], ''.join(align1), ''.join(align2))

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  (cost, align1, align2) = edta(records[0][1], records[1][1])
  print(cost)
  print(align1)
  print(align2)

if __name__ == "__main__":
  main()
