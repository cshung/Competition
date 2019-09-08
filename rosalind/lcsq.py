# http://rosalind.info/problems/lcsq/

from sys import stdin
from libfasta import readFasta
from liblevenshtein import levenshtein

def lcsq(str1, str2):
  m = len(str1)
  n = len(str2)
  (cost, choice) = levenshtein(str1, str2, False)
  #
  # Using the choice array we built, backtrack to find the longest common subsequence
  #
  i = m
  j = n
  answer = []
  while i != 0 and j != 0:
    c = choice[i][j]
    if c == 0:
      i = i - 1
      j = j - 1
      if str1[i] != str2[j]:
        raise ValueError()
      answer.append(str1[i])
    elif c == 1:
      i = i - 1
    elif c == 2:
      j = j - 1
    else:
      raise ValueError()
  answer.reverse()
  return ''.join(answer)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  ans = lcsq(records[0][1], records[1][1])
  print(ans)

if __name__ == "__main__":
  main()
