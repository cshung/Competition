# http://rosalind.info/problems/3sum/

from sys import stdin

def threesum(problem):
  answers = []
  for array in problem:
    seen = {}
    n = len(array)
    answer = None
    for i in range(n):
      v = array[i]
      if -v in seen:
        answer = (seen[-v][0] + 1, seen[-v][1] + 1, i + 1)
        break
      else:
        for j in range(i):
          s = array[j] + array[i]
          seen[s] = (j, i)
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
  answers = threesum(problem)
  for answer in answers:
    if answer is None:
      print(-1)
    else:
      print("%d %d %d" % answer)

if __name__ == "__main__":
  main()
