enum partition_list {}

extension partition_list {
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
    func partition(_ head: ListNode?, _ x: Int) -> ListNode? {
      let smallHead = ListNode()
      var smallTail : ListNode? = smallHead
      let bigHead = ListNode()
      var bigTail : ListNode? = bigHead
      var cur = head
      while cur != nil {
        if cur!.val < x {
          smallTail!.next = cur
          smallTail = cur
        } else {
          bigTail!.next = cur
          bigTail = cur
        }
        cur = cur!.next
      }
      smallTail!.next = bigHead.next
      bigTail!.next = nil
      return smallHead.next
    }
  }
  static func main() {
    let a = ListNode(1)
    let b = ListNode(4)
    let c = ListNode(3)
    let d = ListNode(2)
    let e = ListNode(5)
    let f = ListNode(2)
    a.next = b
    b.next = c
    c.next = d
    d.next = e
    e.next = f
    let r = Solution().partition(a, 3)
    var cur = r;
    while cur != nil {
      print(cur!.val)
      cur = cur!.next
    }
  }
}
