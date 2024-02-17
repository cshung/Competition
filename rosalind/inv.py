# http://rosalind.info/problems/inv/

from sys import stdin

def inv(array):
  def merge(ls, le, rs, re):
    count = 0
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
        if lv <= rv:
          buffer.append(array[l])
          l += 1
        else:
          count += (le - l)
          buffer.append(array[r])
          r += 1
    p = ls
    for i in buffer:
      array[p] = i
      p += 1
    return count

  def helper(s, e):
    l = e - s
    count = 0
    if l > 1:
      m = s + l // 2
      count += helper(s, m)
      count += helper(m, e)
      count += merge(s, m, m , e)
    return count

  return helper(0, len(array))

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  answer = inv([int(x) for x in data[1].split()])
  print(answer)

if __name__ == "__main__":
  main()
