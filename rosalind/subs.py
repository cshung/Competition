# http://rosalind.info/problems/subs/

import six

dna = six.moves.input()
motif = six.moves.input()

index = 0
while True:
  index = dna.find(motif, index)
  if index == -1:
    break
  else:
    index = index + 1
    print(index)
