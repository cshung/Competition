# http://rosalind.info/problems/scsp/

import six
from liblevenshtein import levenshtein

def scsp(str1, str2):
  m = len(str1)
  n = len(str2)
  (cost, choice) = levenshtein(str1, str2, False)
  #
  # Using the choice array we built, backtrack to find the longest common subsequence
  #
  i = m
  j = n
  superstring = []
  while i != 0 or j != 0:
    c = choice[i][j]
    if c == 0:
      i = i - 1
      j = j - 1
      if str1[i] != str2[j]:
        raise ValueError(str(i) + " " + str(j))
      superstring.append(str1[i])
    elif c == 1:
      j = j - 1
      superstring.append(str2[j])
    elif c == 2:
      i = i - 1
      superstring.append(str1[i])
    else:
      raise ValueError()
  superstring.reverse()
  return ''.join(superstring)

def main():
  str1 = six.moves.input()
  str2 = six.moves.input()
  print(scsp(str1, str2))

if __name__ == "__main__":
  main()
