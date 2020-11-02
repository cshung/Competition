# http://rosalind.info/problems/lexv/

from sys import stdin

def lexv(list, n):
  answers = []
  current = []
  while True:
    if len(current) < n:
      current.append(0)
    else:
      if current[-1] == len(list) - 1:
        while current[-1] == len(list) - 1:
          current.pop()
          if len(current) == 0:
            return answers
          if current[-1] < len(list) - 1:
            current[-1] = current[-1] + 1
            break
      else:
        current[-1] = current[-1] + 1
    s = ""
    for i in current:
      s = s + list[i]
    answers.append(s)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  list = data[0].split(' ')
  n = int(data[1])
  answers = lexv(list, n)
  for answer in answers:
    print(answer)

if __name__ == "__main__":
  main()
