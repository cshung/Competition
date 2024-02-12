# http://rosalind.info/problems/nwck/

from sys import stdin
from libnewick import newick

def ctbl(root):
  characters = []
  def helper(tree):
    subanswers = [helper(child) for child in tree[1]]
    s = []
    for subanswer in subanswers:
      s += subanswer
    if len(tree[1]) == 0:
      s.append(tree[0])
    elif tree != root:
      characters.append(s)
    return s
  root = newick(root)
  taxa = helper(root)
  taxa.sort()
  solution = []
  for character in characters:
    s = ""
    for taxon in taxa:
      if taxon in character:
        s += "1"
      else:
        s += "0"
    solution.append(s)
  return solution

def main():
  data = []
  for line in stdin:
    line = line.strip()
    data.append(line.strip())
  tree = data[0]
  for line in ctbl(tree):
    print(line)

if __name__ == "__main__":
  main()