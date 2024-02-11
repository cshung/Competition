# http://rosalind.info/problems/motz/

from sys import stdin
from libfasta import readFasta

def complement(n):
  if n == 'A':
    return 'U'
  elif n == 'C':
    return 'G'
  elif n == 'G':
    return 'C'
  elif n == 'U':
    return 'A'

def motz(problem):
  n = len(problem)
  dp = [[0 for _ in range(n)] for _ in range(n + 1)]
  for start in range(n):
    dp[start][start] = 1
    dp[n][start] = 1
  for start in range(n - 1):
    dp[start + 1][start] = 1
  for length in range(2, n + 1):
    for start in range(0, n + 1 - length): 
      end = start + length - 1
      ans = dp[start + 1][end]
      target = complement(problem[start])
      for search in range(start + 1, end + 1):
        if problem[search] == target:
          ans += dp[start + 1][search - 1] * dp[search + 1][end]
          ans %= 1000000
      dp[start][end] = ans
  return dp[0][n-1]

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  ans = motz(records[0][1])
  print(ans)

if __name__ == "__main__":
  main()
