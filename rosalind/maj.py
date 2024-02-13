# http://rosalind.info/problems/maj/

from sys import stdin

def maj(problem):
  answers = []
  for array in problem:
    best = None
    count = 0
    for n in array:
      if best is None:
        best = n
        count = 1
      elif best == n:
        count += 1
      elif count > 1:
        count -= 1
      else:
        best = n
    count = 0
    for n in array:
      if n == best:
        count += 1
    if count > len(array) // 2:
      answers.append(best)
    else:
      answers.append(-1)
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  n = int(data[0].split()[0])
  problem = []
  for i in range(n):
    problem.append([int(x) for x in data[i + 1].split()])
  print(" ".join([str(x) for x in maj(problem)]))

if __name__ == "__main__":
  main()
