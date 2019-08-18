# http://rosalind.info/problems/perm/

import six
import math

def perm(n):
  answers = []
  perm_worker(range(1, n + 1), 0, answers)
  return answers

def perm_worker(l, i, answers):
  if i == len(l):
    answers.append(' '.join(str(a) for a in l))
  else:
    for j in range(i, len(l)):
      temp = l[i]
      l[i] = l[j]
      l[j] = temp
      perm_worker(l, i + 1, answers)
      temp = l[i]
      l[i] = l[j]
      l[j] = temp

def main():
  n = int(six.moves.input())
  answers = perm(n)
  print(math.factorial(n))
  for answer in answers:
    print(answer)

if __name__ == "__main__":
  main()
