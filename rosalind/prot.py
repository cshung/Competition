# http://rosalind.info/problems/prot/

import six
from lib import code

rna = six.moves.input()

i = 0
protein = ""
while(True):
    if i + 2 < len(rna):
        key = rna[i] + rna[i + 1] + rna[i + 2]
        m = code[key]
        i = i + 3
        if m == "Stop":
            break
        else:
            protein = protein + m
    else:
        break
print(protein)