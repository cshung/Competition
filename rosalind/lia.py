# http://rosalind.info/problems/lia/

from sys import stdin

def lia(n,k):
  population = 2 ** k 
  p = 0.75 ** population
  numerator = population
  denominator = 1
  binomial = 1
  answer = 0
  for r in range(0, n):
    answer = answer + binomial * p
    p = p * 0.25 / 0.75
    binomial = binomial * numerator
    binomial = binomial / denominator
    numerator = numerator - 1
    denominator = denominator + 1
  return (1 - answer)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  line = data[0]
  tokens = line.split(' ')
  k = int(tokens[0])
  n = int(tokens[1])
  answer = lia(n,k)
  print(answer)

if __name__ == "__main__":
  main()
