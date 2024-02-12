def newick(input):
  special = set()
  special.add('(')
  special.add(',')
  special.add(')')
  special.add(';')
  counter = [0]

  def lex():
    tokens = []
    name = ""
    for c in input:
      if c in special:
        if name != "":
          tokens.append(name)
          name = ""
        tokens.append("%s" % c)
      else:
        name += c
    if name != "":
      tokens.append(name)
    tokens.reverse()
    return tokens

  def parseChildrenList(tokens):
    nodes = []
    while True:
      nodes.append(parseNode(tokens))
      if tokens[-1] == ')':
        break
      tokens.pop()
    return nodes

  def parseNode(tokens):
    if tokens[-1] == ','  or tokens[-1] == ')':
      name = "%s" % counter[0]
      counter[0] += 1
      children = []
    elif tokens[-1] == '(':
      tokens.pop()
      children = parseChildrenList(tokens)
      tokens.pop()
      if tokens[-1] not in special:
        name = tokens[-1]
        tokens.pop()
      else:
        name = "%s" % counter[0]
        counter[0] += 1
    elif tokens[-1] not in special:
      name = tokens[-1]
      children = []
      tokens.pop()
    else:
      raise ValueError("No")
    return (name, children)

  return parseNode(lex())

def printTree(tree, indent):
  (name, children) = tree
  print(" " * indent + name)
  for child in children:
    printTree(child, indent + 2)