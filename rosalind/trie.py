# http://rosalind.info/problems/trie/

from sys import stdin

def trie(data):
  root = (1, {})
  counter = [2]
  def insert(s, i, tree):
    if i == len(s):
      return
    else:
      ch = s[i]
      if ch not in tree[1]:
        tree[1][ch] = (counter[0], {})
        counter[0] += 1
      insert(s, i + 1, tree[1][ch])
  def printTrie(tree):
    for k in tree[1]:
      print(tree[0], tree[1][k][0], k)
      printTrie(tree[1][k])
  for s in data:
    insert(s, 0, root)
  printTrie(root)

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  trie(data)

if __name__ == "__main__":
  main()
