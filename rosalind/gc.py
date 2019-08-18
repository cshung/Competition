# http://rosalind.info/problems/gc/

from sys import stdin
from libfasta import readFasta

def gc(records):
  max_gc = -1
  max_gc_label = None
  for (label,dna) in records:
    n = 0.0
    d = 0.0
    for c in dna:
      d = d + 1
      if (c == 'G') or (c == 'C'):
        n = n + 1
    gc = n/d * 100
    if (max_gc == -1) or (gc > max_gc):
      max_gc = gc
      max_gc_label = label
  return (max_gc_label, max_gc)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  (max_gc_label, max_gc) = gc(records)
  print(max_gc_label)
  print(max_gc)

if __name__ == "__main__":
  main()
