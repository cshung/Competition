# http://rosalind.info/problems/dij/

from sys import stdin

def dij(adj):
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

  dists[0] = 0
  insert(0)

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

  return dists

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  tokens = data[0].split()
  n = int(tokens[0])
  m = int(tokens[1])
  adj = [[] for _ in range(n)]
  for i in range(m):
    tokens = data[i + 1].split()
    src = int(tokens[0]) - 1
    dst = int(tokens[1]) - 1
    dist = int(tokens[2])
    adj[src].append((dst, dist))
  answers = dij(adj)
  print(" ".join(str(x) for x in answers))

if __name__ == "__main__":
  main()
