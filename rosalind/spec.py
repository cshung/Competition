# http://rosalind.info/problems/spec/

from sys import stdin
from libcode import mass

def spec(problem):
  problem.sort()
  n = len(problem)
  answer = ""
  for i in range(1, n):
    diff = problem[i] - problem[i - 1]
    best = None
    for residue in mass:
      comp = abs(mass[residue] - diff)
      if best is None or comp < best:
        best = comp
        choice = residue
    answer += choice
  return answer

def main():
  data = []
  for line in stdin:
    data.append(float(line.strip()))
  print(spec(data))

if __name__ == "__main__":
  main()
