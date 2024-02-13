# http://rosalind.info/problems/2sum/

from sys import stdin

def twosum(problem):
  answers = []
  for array in problem:
    seen = {}
    n = len(array)
    answer = None
    for i in range(n):
      v = array[i]
      if -v in seen:
        answer = (seen[-v] + 1, i + 1)
        break
      else:
        seen[v] = i
    answers.append(answer)
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  n = int(data[0].split()[0])
  problem = []
  for i in range(n):
    problem.append([int(x) for x in data[i+1].split()])
  answers = twosum(problem)
  for answer in answers:
    if answer is None:
      print(-1)
    else:
      print("%d %d" % answer)

if __name__ == "__main__":
  main()
