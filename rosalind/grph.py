# http://rosalind.info/problems/grph/

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

for (label1, dna1) in records:
  for (label2, dna2) in records:
    if len(dna1) >= 3 and len(dna2) >= 3 and dna1 != dna2 and dna1[len(dna1) - 3: len(dna1)] == dna2[0:3]:
      print("%s %s" % (label1, label2))