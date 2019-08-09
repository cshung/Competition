# http://rosalind.info/problems/perm/

import six
import math

def perm(l, i, s):
    if i == len(l):
        print(s)
    else:
        for j in range(i, len(l)):
            temp = l[i]
            l[i] = l[j]
            l[j] = temp
            perm(l, i + 1, s + str(l[i]) + " ")
            temp = l[i]
            l[i] = l[j]
            l[j] = temp

n = int(six.moves.input())

print(math.factorial(n))
perm(range(1, n + 1), 0, "")
