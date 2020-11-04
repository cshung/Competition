# http://rosalind.info/problems/seto/

from sys import stdin

def seto(n, set1, set2):
  union = []
  intersection = []
  a_except_b = []
  b_except_a = []
  a_complement = []
  b_complement = []
  for i in range(1, n + 1):
    one = i in set1
    two = i in set2
    if one or two:
      union.append(i)
    if one and two:
      intersection.append(i)
    if one and not two:
      a_except_b.append(i)
    if not one and two:
      b_except_a.append(i)
    if not one:
      a_complement.append(i)
    if not two:
      b_complement.append(i)
  return (union, intersection, a_except_b, b_except_a, a_complement, b_complement)

def toSet(str):
  s = {}
  for element in toList(str):
    s[element] = True
  return s

def toList(str):
  return [int(token) for token in str.replace("{","").replace("}","").replace(",","").split(" ")]

def toStr(list):
  return "{" + ", ".join(str(element) for element in list) + "}"

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  n = int(data[0])
  set1 = toSet(data[1])
  set2 = toSet(data[2])
  (union, intersection, a_except_b, b_except_a, a_complement, b_complement) = seto(n, set1, set2)
  print(toStr(union))
  print(toStr(intersection))
  print(toStr(a_except_b))
  print(toStr(b_except_a))
  print(toStr(a_complement))
  print(toStr(b_complement))

if __name__ == "__main__":
  main()
