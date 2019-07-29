# http://rosalind.info/problems/hamm/

import six

dna1 = six.moves.input()
dna2 = six.moves.input()

answer = 0
for i in range(0, len(dna1)):
  if not dna1[i] == dna2[i]:
    answer = answer + 1
print(answer)
