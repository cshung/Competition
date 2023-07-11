enum all_nodes_distance_k_in_binary_tree {}

extension all_nodes_distance_k_in_binary_tree {
  class Node {
    var value: Int
    var depth: Int
    var parent: Int
    var next: Node?
    weak var prev: Node?

    init() {
      value = 0
      depth = 0
      parent = 0
    }
  }
  public class TreeNode {
    public var val: Int
    public var left: TreeNode?
    public var right: TreeNode?
    public init() {
      self.val = 0
      self.left = nil
      self.right = nil
    }
    public init(_ val: Int) {
      self.val = val
      self.left = nil
      self.right = nil
    }
    public init(_ val: Int, _ left: TreeNode?, _ right: TreeNode?) {
      self.val = val
      self.left = left
      self.right = right
    }
  }
  class Solution {
    func build(_ root: TreeNode, _ adj: inout [Int: [Int]]) {
      adj[root.val] = []
      if let left = root.left {
        build(left, &adj)
        adj[root.val]!.append(left.val)
        adj[left.val]!.append(root.val)
      }
      if let right = root.right {
        build(right, &adj)
        adj[root.val]!.append(right.val)
        adj[right.val]!.append(root.val)
      }
    }
    func enqueue(_ head: inout Node, _ value: Int, _ depth: Int, _ parent: Int) {
      let newNode = Node()
      newNode.value = value
      newNode.depth = depth
      newNode.parent = parent
      newNode.prev = head
      newNode.next = head.next
      newNode.prev!.next = newNode
      newNode.next!.prev = newNode
    }
    func dequeue(_ tail: inout Node) -> (Int, Int, Int) {
      let answer = tail.prev!
      answer.next!.prev = answer.prev
      answer.prev!.next = answer.next
      return (answer.value, answer.depth, answer.parent)
    }
    func distanceK(_ root: TreeNode?, _ target: TreeNode?, _ k: Int) -> [Int] {
      var adj = [Int: [Int]]()
      build(root!, &adj)
      var head = Node()
      var tail = Node()
      head.next = tail
      tail.prev = head
      enqueue(&head, target!.val, 0, -1)
      var answers : [Int] = []
      while !(head.next === tail) {
        let (value, depth, parent) = dequeue(&tail)
        let neighbors = adj[value]!
        for i in 0..<neighbors.count {
          let neighbor = neighbors[i]
          if neighbor != parent {
            if depth + 1 == k {
              answers.append(neighbor)
            } else {
              enqueue(&head, neighbor, depth + 1, value)
            }
          }
        }
      }

      return answers
    }
  }
  static func main() {
    let s = Solution()
    let a = TreeNode(3, Optional.none, Optional.none)
    let b = TreeNode(5, Optional.none, Optional.none)
    let c = TreeNode(1, Optional.none, Optional.none)
    let d = TreeNode(6, Optional.none, Optional.none)
    let e = TreeNode(2, Optional.none, Optional.none)
    let f = TreeNode(0, Optional.none, Optional.none)
    let g = TreeNode(8, Optional.none, Optional.none)
    let h = TreeNode(7, Optional.none, Optional.none)
    let i = TreeNode(4, Optional.none, Optional.none)
    a.left = b
    a.right = c
    b.left = d
    b.right = e
    c.left = f
    c.right = g
    e.left = h
    e.right = i
    print(s.distanceK(a, b, 2))
  }
}
