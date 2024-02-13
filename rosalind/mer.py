# http://rosalind.info/problems/mer/

from sys import stdin

def mer(left, right):
  answer = []
  p = 0
  q = 0
  while True:
    if p == len(left):
      if q == len(right):
        break
      else:
        answer.append(right[q])
        q += 1
    elif q == len(right):
      answer.append(left[p])
      p += 1
    else:
      l = left[p]
      r = right[q]
      if l < r:
        answer.append(left[p])
        p += 1
      else:
        answer.append(right[q])
        q += 1
  return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  left = [int(x) for x in data[1].split()]
  right = [int(x) for x in data[3].split()]
  print(" ".join([str(x) for x in mer(left, right)]))

if __name__ == "__main__":
  main()
