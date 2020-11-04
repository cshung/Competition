# http://rosalind.info/problems/lexf/

from sys import stdin

def lexf(alphabets, n):
  results = []
  for i in range(0, len(alphabets) ** n):
    temp = i
    s = ""
    for j in range(0, n):
      s = alphabets[temp % len(alphabets)] + s 
      temp = temp // len(alphabets)
    results.append(s)
  return results

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  alphabets = data[0].split(' ')
  n = int(data[1])
  results = lexf(alphabets, n)
  for result in results:
    print(result)

if __name__ == "__main__":
  main()
