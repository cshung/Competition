# http://rosalind.info/problems/fib/

import six

def power(a,b,c,d,n):
  if n == 0:
    return (1,0,0,1)
  elif n == 1:
    return (a,b,c,d)
  else:
    half = n // 2;
    (p,q,r,s) = power(a,b,c,d,half)
    e = p * p + q * r
    f = p * q + q * s
    g = r * p + s * r
    h = r * q + s * s
    if half * 2 < n:
      i = e * a + f * c
      j = e * b + f * d
      k = g * a + h * c
      l = g * b + h * d
      return (i,j,k,l)
    else:
      return (e,f,g,h)

n = int(six.moves.input())
k = int(six.moves.input())

(a,b,c,d) = power(0,k,1,1,n - 1)
print("%d" % (a + c))

