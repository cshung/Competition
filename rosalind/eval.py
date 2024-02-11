# http://rosalind.info/problems/eval/

from sys import stdin
from math import comb

def eval(n,s,a):
  answers = []
  for gc in a:
    p = 1
    prob = {}
    half = gc/2
    other = (1 - gc)/2
    prob['A'] = other
    prob['C'] = half
    prob['T'] = other
    prob['G'] = half
    for ch in s:
      p *= prob[ch]
    p *= (n - 1)
    answers.append(p)
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  n = int(data[0])
  s = data[1]
  a = [float(token) for token in data[2].split(' ')]
  answers = eval(n,s,a)
  print(" ".join([("%.4f" % i) for i in answers]))

if __name__ == "__main__":
  main()
