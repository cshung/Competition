# http://rosalind.info/problems/ins/

from sys import stdin

def ins(array):
  n = len(array)
  swaps = 0
  for i in range(2, n + 1):
    k = i
    while k > 1 and array[k - 1] < array[k - 2]:
      temp = array[k - 1]
      array[k - 1] = array[k - 2]
      array[k - 2] = temp
      swaps += 1
      k -= 1
  return swaps

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  array = [int(x) for x in data[1].split()]
  print(ins(array))

if __name__ == "__main__":
  main()
