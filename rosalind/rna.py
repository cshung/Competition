# http://rosalind.info/problems/rna/

import six

dna = six.moves.input()
rna = dna.replace("T","U")
print(rna)