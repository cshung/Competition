# http://rosalind.info/problems/iprb/

import six

line = six.moves.input()
tokens = line.split(' ')
k = int(tokens[0])
m = int(tokens[1])
n = int(tokens[2])
N = k + m + n
C = N * (N - 1) * 4.0
R = n * (n - 1) * 4 + (m * n * 2) * 2 + (m * (m - 1)) * 1
print(1 - R/C)