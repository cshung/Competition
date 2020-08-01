# http://rosalind.info/problems/kmp/

from sys import stdin
from libfasta import readFasta
from libkmp import build_z

def kmp(dna):
  z = build_z(dna)
  failure = [0] * len(dna)
  r = -1
  state = [(0, 0)] * len(dna)
  for i in range(0, len(dna)):
    if z[i] > 0:
      if i > r:
        state[i] = (1, z[i])
        r = i + z[i] - 1
      elif i + z[i] - 1 > r:
        state[r + 1] = (r - i + 2, z[i])
        r = i + z[i] - 1
    (v,e) = state[i]
    if v > 0:
      failure[i] = v
      if v < e:
        state[i + 1] = (v + 1, e)
  return " ".join([str(i) for i in failure])

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  print(kmp(records[0][1]))
  
if __name__ == "__main__":
  main()
