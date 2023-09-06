enum split_linked_list_in_parts {}

extension split_linked_list_in_parts {

  public class ListNode {
    public var val: Int
    public var next: ListNode?
    public init() {
      self.val = 0
      self.next = nil
    }
    public init(_ val: Int) {
      self.val = val
      self.next = nil
    }
    public init(_ val: Int, _ next: ListNode?) {
      self.val = val
      self.next = next
    }
  }

  class Solution {
    func splitListToParts(_ head: ListNode?, _ k: Int) -> [ListNode?] {
      var cur = head
      var nodes: [ListNode] = []
      while cur != nil {
        let curr = cur!
        nodes.append(curr)
        cur = curr.next
      }
      let len = nodes.count
      let piece = len / k
      var rem = len % k
      var answers: [ListNode?] = []
      var c = 0

      for _ in 0..<k {
        if c < len {
          answers.append(nodes[c])
        } else {
          answers.append(nil)
        }
        c += piece
        if rem > 0 {
          c += 1
          rem -= 1
        }
        if c > 0 {
          nodes[c - 1].next = nil
        }
      }
      return answers
    }
  }
  static func main() {
    let a = ListNode(1)
    let b = ListNode(2)
    let c = ListNode(3)
    a.next = b
    b.next = c
    let answers = Solution().splitListToParts(a, 5)
    for answer in answers {
      var cur = answer
      print("[", terminator: "")
      while cur != nil {
        let curr = cur!
        print(curr.val, terminator: " ")
        cur = curr.next
      }
      print("]")
    }
  }
}
