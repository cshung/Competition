# http://rosalind.info/problems/mrna/

from sys import stdin
from libcode import code

def mrna(protein):
  back = {}
  for key in code:
    value = code[key]
    if value in back:
      back[value] = back[value] + 1
    else:
      back[value] = 1
  answer = 1
  for b in protein:
    answer = (answer * back[b]) % 1000000
  answer = (answer * back["Stop"]) % 1000000
  return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  protein = data[0]
  answer = mrna(protein)
  print(answer)

if __name__ == "__main__":
  main()
