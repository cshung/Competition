from math import factorial

def encode(perm):
  code = list(perm)
  for i in range(0, len(code)):
    count = 0
    for j in range(i + 1, len(code)):
      if code[i] > code[j]:
        count = count + 1
      else:
        code[j] = code[j] - 1
  answer = 0
  for i in range(0, len(code)):
    answer = answer + factorial(i) * code[len(code) - i - 1]
  return answer

def decode(n, length):
  perm = [0] * length
  for i in range(0, length):
    remainder = n % (i + 1)
    perm[length - 1 - i] = remainder
    n = n // (i + 1)
  for k in range(0, len(perm)):
    i = len(perm) - k - 1
    count = 0
    for j in range(i + 1, len(perm)):
      if perm[i] > perm[j]:
        count = count + 1
      else:
        perm[j] = perm[j] + 1
  return perm