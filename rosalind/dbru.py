# http://rosalind.info/problems/revc/

from sys import stdin

def complement(n):
  if n == 'A':
    return 'T'
  elif n == 'C':
    return 'G'
  elif n == 'G':
    return 'C'
  elif n == 'T':
    return 'A'

def reverse_complement(s):
  r = ""
  for c in s:
    r = complement(c) + r
  return r

def dbru(pieces):
  pieces = set(pieces)
  revs = set()
  for piece in pieces:
    rev = reverse_complement(piece)
    revs.add(rev)
  pieces |= revs
  pieces = list(pieces)
  pieces.sort()
  answers = []
  for piece in pieces:
    answer = (piece[:-1], piece[1:])
    answers.append(answer)
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answers = dbru(data)
  for answer in answers:
    print("(%s, %s)" % answer)

if __name__ == "__main__":
  main()

