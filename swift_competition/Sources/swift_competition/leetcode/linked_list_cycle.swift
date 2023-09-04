enum linked_list_cycle {}

extension linked_list_cycle {
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
    func hasCycle(_ head: ListNode?) -> Bool {
      guard let head = head else {
        return false
      }

      var fast: ListNode? = head
      var slow: ListNode? = head

      while true {
        fast = fast?.next
        if fast == nil {
          return false
        }

        fast = fast?.next
        if fast == nil {
          return false
        }

        slow = slow?.next
        if fast === slow {
          return true
        }
      }
    }
  }
  static func main() {
    let a = ListNode(3)
    let b = ListNode(2)
    let c = ListNode(0)
    let d = ListNode(4)
    a.next = b;
    b.next = c;
    c.next = d;
    d.next = b;
    print(Solution().hasCycle(a));
    d.next = nil
  }
}
