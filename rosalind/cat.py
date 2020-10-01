# http://rosalind.info/problems/cat/

from sys import stdin
from libfasta import readFasta

def cat(rna):
  last_same = [-1] * 4
  last_unpaireds = []
  last_unpaireds.append([])
  last_unpaireds.append([])
  last_unpaireds.append([])
  last_unpaireds.append([])
  indexes = {}
  indexes['A'] = 0;
  indexes['U'] = 1;
  indexes['C'] = 2;
  indexes['G'] = 3;
  partners = [1, 0, 3, 2]
  next_same = [-1] * len(rna)
  next_pair = [-1] * len(rna)
  for i in range(0, len(rna)):
    n = rna[i]    
    index = indexes[n]
    partner = partners[index]
    if last_same[index] != -1:
      next_same[last_same[index]] = i
    last_same[index] = i
    for last_unpaired in last_unpaireds[partner]:
      next_pair[last_unpaired] = i
    last_unpaireds[partner] = []
    last_unpaireds[index].append(i)
  memo = {}
  return solve(memo, next_same, next_pair, rna, 0, len(rna))

def solve(memo, next_same, next_pair, rna, start, end):
  if start == end:
    return 1
  if (end - start) % 2 == 1:
    return 0
  key = (start, end)
  if key in memo:
    return memo[key]
  else:
    answer = 0
    n = next_pair[start]
    while n != -1 and n < end:
      product = (solve(memo, next_same, next_pair, rna, start + 1, n) * solve(memo, next_same, next_pair, rna, n + 1, end)) % 1000000
      answer = (answer + product) % 1000000
      n = next_same[n]
    memo[key] = answer
    return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  ans = cat(records[0][1])
  print(ans)

if __name__ == "__main__":
  main()
