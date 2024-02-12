# http://rosalind.info/problems/nwck/

from sys import stdin
from libnewick import newick

def nwck(tree, a, b):
  def helper(tree, depth):
    (name, children) = tree
    subanswers = [helper(child, depth + 1) for child in children]
    a_depth = depth if name == a else None
    b_depth = depth if name == b else None
    solution = None
    for (sub_a_depth, sub_b_depth, sub_solution) in subanswers:
      if sub_a_depth is not None:
        a_depth = sub_a_depth
      if sub_b_depth is not None:
        b_depth = sub_b_depth
      if sub_solution is not None:
        solution = sub_solution
    if a_depth is not None and b_depth is not None and solution is None:
      solution = a_depth - depth + b_depth - depth
    return (a_depth, b_depth, solution)
  return helper(newick(tree), 0)[2]

def main():
  data = []
  for line in stdin:
    line = line.strip()
    if len(line) > 0:
      data.append(line.strip())
  n = len(data) // 2
  for i in range(n):
    tree = data[i * 2]
    pair = data[i * 2 + 1].split(' ')
    print(nwck(tree, pair[0], pair[1]))

if __name__ == "__main__":
  main()