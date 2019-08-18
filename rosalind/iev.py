# http://rosalind.info/problems/iev/

import six

def iev(a,b,c,d,e,f):
  return ((4 * a + 4 * b + 4 * c + 3 * d + 2 * e) / 2.0)

def main():
  line = six.moves.input()
  tokens = line.split(' ')
  a = int(tokens[0])
  b = int(tokens[1])
  c = int(tokens[2])
  d = int(tokens[3])
  e = int(tokens[4])
  f = int(tokens[5])
  answer = iev(a,b,c,d,e,f)
  print(answer)

if __name__ == "__main__":
  main()
