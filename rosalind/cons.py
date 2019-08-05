# http://rosalind.info/problems/cons/

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
      records.append(dna)
    label = line[1:]
    dna = ""
  else:
    dna = dna + line

length = len(records[0])
stats = []

for i in range(0, length):
    stats.append({"A":0,"C":0,"G":0,"T":0})
    for record in records:
        c = record[i]
        stats[i][c] = stats[i][c] + 1

consensus = ""
a_line = "A:"
c_line = "C:"
g_line = "G:"
t_line = "T:"
for i in range(0, length):
    a = stats[i]['A']
    c = stats[i]['C']
    g = stats[i]['G']
    t = stats[i]['T']
    m = max([a,c,g,t])
    if (m == a):
        consensus = consensus + 'A'
    elif (m == c):
        consensus = consensus + 'C'
    elif (m == g):
        consensus = consensus + 'G'
    elif (m == t):
        consensus = consensus + 'T'
    a_line = a_line + " " + str(a)
    c_line = c_line + " " + str(c)
    g_line = g_line + " " + str(g)
    t_line = t_line + " " + str(t)

print(consensus)
print(a_line)
print(c_line)
print(g_line)
print(t_line)
