# http://rosalind.info/problems/cons/

from sys import stdin
from libfasta import readFasta

def cons(records):
  length = len(records[0][1])
  stats = []
  for i in range(0, length):
    stats.append({"A":0,"C":0,"G":0,"T":0})
    for (_, record) in records:
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
  return (consensus, a_line, c_line, g_line, t_line)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  (consensus, a_line, c_line, g_line, t_line) = cons(records)
  print(consensus)
  print(a_line)
  print(c_line)
  print(g_line)
  print(t_line)

if __name__ == "__main__":
  main()

