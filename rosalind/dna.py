# http://rosalind.info/problems/dna/

import six

dna = six.moves.input()
a = 0
c = 0
g = 0
t = 0
for n in dna:
  if n == 'A':
    a = a + 1
  elif n == 'C':
    c = c + 1
  elif n == 'G':
    g = g + 1
  elif n == 'T':
    t = t + 1
print("%d %d %d %d" % (a,c,g,t))
