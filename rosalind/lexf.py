# http://rosalind.info/problems/lexf/

import six

def lexf(alphabets, n):
  results = []
  for i in range(0, len(alphabets) ** n):
    temp = i
    s = ""
    for j in range(0, n):
      s = alphabets[temp % len(alphabets)] + s 
      temp = temp // len(alphabets)
    results.append(s)
  return results

def main():
  problem = six.moves.input()
  alphabets = problem.split(' ')
  n = int(six.moves.input())
  results = lexf(alphabets, n)
  for result in results:
    print(result)

if __name__ == "__main__":
  main()
