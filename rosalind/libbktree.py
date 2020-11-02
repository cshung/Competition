class bktree:
  class node:
    def __init__(self, word):
      self.word = word
      self.children = {}

  def __init__(self, dist):
    self.__root = None
    self.__dist = dist

  def insert(self, word):
    if self.__root == None:
      self.__root = self.node(word)
    else:
      current = self.__root
      while True:
        distance = self.__dist(word, current.word)
        if distance in current.children:
          current = current.children[distance]
        else:
          current.children[distance] = self.node(word)
          break

  def query(self, word, n):
    if self.__root == None:
      return []
    else:
      answer = []
      self.__query(self.__root, word, n, answer)
      return answer

  def __query(self, node, word, n, answer):
    distance = self.__dist(word, node.word)
    if distance <= n:
      answer.append(node.word)
    for i in range(distance - n, distance + n + 1):
      if i in node.children:
        self.__query(node.children[i], word, n, answer)

  def __tostring(self, node, d, indent):
    s = ""
    for i in range(0, indent):
      s = s + " "
    s = s + str(d) + ":" + node.word + "\n"
    for key in node.children:
      s = s + self.__tostring(node.children[key], key, indent + 2)
    return s

  def __str__(self):
    if self.__root == None:
      return "None"
    else:
      return self.__tostring(self.__root, 0, 0)
