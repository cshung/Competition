# http://rosalind.info/problems/gc/

from sys import stdin

data = []
for line in stdin:
  data.append(line.strip())
data.append(">")

records = []
label = None
dna = ""
for line in data:
  if line[0] == '>':
    if label != None:
      records.append((label, dna))
    label = line[1:] 
    dna = ""
  else:
    dna = dna + line

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

print(max_gc_label)
print(max_gc)
