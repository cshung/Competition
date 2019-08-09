# http://rosalind.info/problems/mrna/

import six
from lib import code

rna = six.moves.input()
back = {}
for key in code:
    value = code[key]
    if value in back:
        back[value] = back[value] + 1
    else:
        back[value] = 1

answer = 1
for b in rna:
    answer = (answer * back[b]) % 1000000
answer = (answer * back["Stop"]) % 1000000
print(answer)