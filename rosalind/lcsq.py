# http://rosalind.info/problems/lcsq/

from sys import stdin
from libfasta import readFasta

def lcsq(str1, str2):
  m = len(str1)
  n = len(str2)
  #
  # cost[i][j] represents the minimum cost of editing str1[0, i) to str2[0, j)
  # choice[i][j] records the last editing operation used.
  #
  # There are two editing operation that we could use:
  # Insert a character  (choice = 1)
  # Delete a character  (choice = 2)
  # Each of them has a cost of 1
  #  
  cost = [[0 for i in range(0, n + 1)] for j in range(0, m + 1)]   
  choice = [[-1 for i in range(0, n + 1)] for j in range(0, m + 1)] 
  #
  # If str2 is the empty string, the only reasonable editing operation is deleting character from str1
  #
  for i in range(0, m + 1):
    cost[i][0] = i
    choice[i][0] = 2
  #
  # If str1 is the empty string, the only reasonable editing operation is inserting character to str1
  #
  for j in range(0, n + 1):
    cost[0][j] = j
    choice[0][j] = 1
  #
  # Otherwise we use this dynamic programming algorithm
  #
  for i in range(1, m + 1):
    for j in range(1, n + 1):
      c1 = str1[i - 1]
      c2 = str2[j - 1]
      if c1 == c2:
        # If the last character happens to match, there is no need to do any operation
        cost[i][j] = cost[i - 1][j - 1]
        choice[i][j] = 0
      else:
        # Otherwise there are only two choices left, either we choose to insert or delete
        insertion_cost = cost[i - 1][j] + 1
        deletion_cost = cost[i][j - 1] + 1
        cost[i][j] = min(insertion_cost, deletion_cost)
        if cost[i][j] == insertion_cost:
          choice[i][j] = 1
        elif cost[i][j] == deletion_cost:
          choice[i][j] = 2
        else:
          raise ValueError()
      if choice[i][j] == -1:
        raise ValueError()
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
