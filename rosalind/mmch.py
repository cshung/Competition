# http://rosalind.info/problems/mmch/

from sys import stdin
from libfasta import readFasta

def mmch(rna):
  counts = {}
  counts['A'] = 0
  counts['U'] = 0
  counts['C'] = 0
  counts['G'] = 0
  for n in rna:
    counts[n] = counts[n] + 1
  max_au = max(counts['A'], counts['U'])
  min_au = min(counts['A'], counts['U'])
  max_cg = max(counts['C'], counts['G'])
  min_cg = min(counts['C'], counts['G'])
  ans = 1
  for i in range(max_au - min_au, max_au):
    ans = ans * (i + 1)
  for i in range(max_cg - min_cg, max_cg):
    ans = ans * (i + 1)
  return ans

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  ans = mmch(records[0][1])
  print(ans)

if __name__ == "__main__":
  main()
