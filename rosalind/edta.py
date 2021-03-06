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
  while i != 0 or j != 0:
    c = choice[i][j]
    if c == 0:
      i = i - 1
      j = j - 1
      if str1[i] != str2[j]:
        raise ValueError()
      align1.append(str1[i])
      align2.append(str2[j])
    elif c == 1:
      j = j - 1
      align1.append('-')
      align2.append(str2[j])
    elif c == 2:
      i = i - 1
      align1.append(str1[i])
      align2.append('-')
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
  if len(align1) != len(align2):
    raise ValueError()
  count = 0
  for i in range(0, len(align1)):
    if align1[i] != align2[i]:
      count = count + 1
  if count != cost:
    raise ValueError()
  if align1.replace("-","") != records[0][1]:
    raise ValueError()
  if align2.replace("-","") != records[1][1]:
    raise ValueError()

if __name__ == "__main__":
  main()
