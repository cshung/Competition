from sys import stdin
from libfasta import readFasta

def kmer(dna):
  map = {}
  map['A'] = 0
  map['C'] = 1
  map['G'] = 2
  map['T'] = 3
  answer = [0] * 256
  for i in range(0, len(dna) - 3):
    a = map[dna[i]]
    b = map[dna[i + 1]]
    c = map[dna[i + 2]]
    d = map[dna[i + 3]]
    code = a * 64 + b * 16 + c * 4 + d
    answer[code] = answer[code] + 1
  return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  print(kmer(records[0][1]))

if __name__ == "__main__":
  main()

