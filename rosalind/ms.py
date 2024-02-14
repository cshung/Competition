# http://rosalind.info/problems/ms/

from sys import stdin

def ms(array):
  def merge(ls, le, rs, re):
    l = ls
    r = rs
    buffer = []
    while True:
      if l == le:
        if r == re:
          break
        else:
          buffer.append(array[r])
          r += 1
      elif r == re:
        buffer.append(array[l])
        l += 1
      else:
        lv = array[l]
        rv = array[r]
        if lv < rv:
          buffer.append(array[l])
          l += 1
        else:
          buffer.append(array[r])
          r += 1
    p = ls
    for i in buffer:
      array[p] = i
      p += 1
  def helper(s, e):
    l = e - s
    if l > 1:
      m = s + l // 2
      helper(s, m)
      helper(m, e)
      merge(s, m, m , e)
  helper(0, len(array))
  return array

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answers = ms([int(x) for x in data[1].split()])
  print(" ".join([str(x) for x in answers]))

if __name__ == "__main__":
  main()
