# http://rosalind.info/problems/cte/

from sys import stdin

def cte(problems):
  answers = []
  for (adj, edge) in problems:
    n = len(adj)
    count = [0]
    dists = [-1] * n
    queue = [-1] * n
    index = [-1] * n

    def assign(queue_index, node):
      queue[queue_index] = node
      index[node] = queue_index

    def bubble_up(queue_index):
      while True:
        if queue_index == 0:
          break
        parent_index = (queue_index + 1) // 2 - 1
        node = queue[queue_index]
        parent = queue[parent_index]
        if dists[node] < dists[parent]:
          assign(queue_index, parent)
          assign(parent_index, node)
          queue_index = parent_index
        else:
          break

    def stone_down(queue_index):
      while True:
        node = queue[queue_index]
        left_child_index = queue_index * 2 + 1
        right_child_index = queue_index * 2 + 2
        if left_child_index >= count[0]:
          break
        elif right_child_index >= count[0]:
          left = queue[left_child_index]
          if dists[node] > dists[left]:
            assign(queue_index, left)
            assign(left_child_index, node)
            queue_index = left_child_index
          else:
            break
        else:
          left = queue[left_child_index]
          right = queue[right_child_index]
          if dists[left] < dists[right]:
            small = left
            small_index = left_child_index
          else:
            small = right
            small_index = right_child_index
          if dists[node] > dists[small]:
            assign(queue_index, small)
            assign(small_index, node)
            queue_index = small_index
          else:
            break

    def insert(node):
      assign(count[0], node)
      bubble_up(count[0])
      count[0] += 1

    def delete_min():
      answer = queue[0]
      count[0] -= 1
      if count[0] > 0:
        assign(0, queue[count[0]])
        stone_down(0)
      queue[count[0]] = -1
      index[answer] = -1
      return answer

    def update(dst):
      stone_down(index[dst])

    dists[edge[1]] = 0
    insert(edge[1])

    while count[0] > 0:
      cur = delete_min()
      for (dst, w) in adj[cur]:
        new_dist = dists[cur] + w
        if dists[dst] == -1:
          dists[dst] = new_dist
          insert(dst)
        elif new_dist < dists[dst]:
          dists[dst] = new_dist
          update(dst)
    
    if dists[edge[0]] == -1:
      answers.append(-1)
    else:
      answers.append(dists[edge[0]] + edge[2])

  return answers

def main():
  data = []
  for line in stdin:
    line = line.strip()
    if len(line) > 0:
      data.append(line)
  l = 0
  tokens = data[l].split()
  g = int(tokens[0])
  l += 1
  problems = []
  for _ in range(g):
    tokens = data[l].split()
    l += 1
    n = int(tokens[0])
    m = int(tokens[1])
    adj = [[] for _ in range(n)]
    first = True
    for i in range(m):
      tokens = data[l].split()
      l += 1
      src = int(tokens[0]) - 1
      dst = int(tokens[1]) - 1
      dist = int(tokens[2])
      if first:
        edge = (src, dst, dist)
        first = False
      adj[src].append((dst, dist))
    problems.append((adj, edge))
  answers = cte(problems)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
