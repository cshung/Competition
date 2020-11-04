# http://rosalind.info/problems/hamm/

from sys import stdin

def hamm(dna1, dna2):
  answer = 0
  for i in range(0, len(dna1)):
    if not dna1[i] == dna2[i]:
      answer = answer + 1
  return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  dna1 = data[0]
  dna2 = data[1]
  answer = hamm(dna1, dna2)
  print(answer)

if __name__ == "__main__":
  main()
