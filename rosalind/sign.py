# http://rosalind.info/problems/sign/

import six
import math

def sign(n):
  answers = []
  sign_worker(range(1, n + 1), 0, answers)
  return answers

def build(prefix, l, i, answers):
    if i == len(l):
        answers.append(prefix.strip())
    else:
        build(prefix + ' ' + str(-l[i]), l, i + 1, answers)
        build(prefix + ' ' + str(l[i]), l, i + 1, answers)        


def sign_worker(l, i, answers):
  if i == len(l):
      build("", l, 0, answers)
  else:
    for j in range(i, len(l)):
      temp = l[i]
      l[i] = l[j]
      l[j] = temp
      sign_worker(l, i + 1, answers)
      temp = l[i]
      l[i] = l[j]
      l[j] = temp

def main():
  n = int(six.moves.input())
  answers = sign(n)
  print(len(answers))
  for answer in answers:
    print(answer)

if __name__ == "__main__":
  main()
