# http://rosalind.info/problems/med/

from sys import stdin

def med(array, k):
  def par(i, j):
    n = len(array)
    p = i
    q = i + 1
    r = j - 1
    pivot = array[i]
    while True:
      #
      # Loop invariants
      # array[i, p) < pivot
      # array[p, q) = pivot
      # array(j, n) > pivot
      #
      while r > q and array[r] > pivot:
        r -= 1
      #
      # At this point, unless r == q, otherwise array[r] <= pivot
      #
      while q < r and array[q] <= pivot:
        if array[q] < pivot:
          array[p], array[q] = array[q], array[p]
          p += 1
        q += 1
      #
      # At this point, unless r == q, otherwise array[q] > pivot
      #
      if r == q:
        #
        # The loop invariant does not include what happen with array[q]
        # fix that here.
        #
        if array[q] < pivot:
          array[p], array[q] = array[q], array[p]
          p += 1
          q += 1
        elif array[q] == pivot:
          q += 1
        break
      #
      # Note that we do not adjust q here, that saves us from determining
      # whether array[q] == pivot or not, the invariants stay correct that way
      #
      array[r], array[q] = array[q], array[r]
      r -= 1
    return (p, q)
  def select(i, j, k):
    if j - i == 1:
      return array[i]
    (p, q) = par(i, j)
    if k < p:
      return select(i, p, k)
    elif k < q:
      return array[p]
    else:
      return select(q, j, k)
  return select(0, len(array), k)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answer = med([int(x) for x in data[1].split()], int(data[2]) - 1)
  print(answer)

if __name__ == "__main__":
  main()
