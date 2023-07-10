enum minimum_depth_of_binary_tree {}

extension minimum_depth_of_binary_tree {
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
    func minDepth(_ root: TreeNode?) -> Int {
      if let root = root {
        let left = root.left.map(minDepth)
        let right = root.right.map(minDepth)
        if let left = left {
          if let right = right {
            return 1 + min(left, right)
          } else {
            return 1 + left
          }
        } else {
          if let right = right {
            return 1 + right
          } else {
            return 1
          }
        }
      } else {
        return 0
      }
    }
  }
  static func main() {
    let s = Solution()
    let a = TreeNode(3, Optional.none, Optional.none)
    let b = TreeNode(9, Optional.none, Optional.none)
    let c = TreeNode(20, Optional.none, Optional.none)
    let d = TreeNode(15, Optional.none, Optional.none)
    let e = TreeNode(7, Optional.none, Optional.none)
    a.left = b
    a.right = c
    c.left = d
    c.right = e
    print(s.minDepth(a))
  }
}
