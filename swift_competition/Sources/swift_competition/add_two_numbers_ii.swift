enum add_two_numbers_ii {}

extension add_two_numbers_ii {

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
    func length(_ l: ListNode?) -> Int {
      if let l = l {
        return 1 + length(l.next)
      } else {
        return 0
      }
    }
    func addTwoNumbers(_ l1: ListNode?, _ length1: Int, _ l2: ListNode?, _ length2: Int) -> (
      ListNode?, Int
    ) {
      if length1 > length2 {
        let (tail, carry) = addTwoNumbers(l1!.next, length1 - 1, l2, length2)
        var msb = l1!.val + carry
        var new_carry = 0
        if msb > 10 {
          msb -= 10
          new_carry = 1
        }
        let result = ListNode(msb)
        result.next = tail
        return (result, new_carry)
      } else if length1 < length2 {
        let (tail, carry) = addTwoNumbers(l1, length1, l2!.next, length2 - 1)
        var msb = l2!.val + carry
        var new_carry = 0
        if msb >= 10 {
          msb -= 10
          new_carry = 1
        }
        let result = ListNode(msb)
        result.next = tail
        return (result, new_carry)
      } else if length1 > 0 && length2 > 0 {
        let (tail, carry) = addTwoNumbers(l1!.next, length1 - 1, l2!.next, length2 - 1)
        var msb = l1!.val + l2!.val + carry
        var new_carry = 0
        if msb >= 10 {
          msb -= 10
          new_carry = 1
        }
        let result = ListNode(msb)
        result.next = tail
        return (result, new_carry)
      } else {
        return (nil, 0)
      }
    }
    func addTwoNumbers(_ l1: ListNode?, _ l2: ListNode?) -> ListNode? {
      let length1 = length(l1)
      let length2 = length(l2)
      let (result, carry) = addTwoNumbers(l1, length1, l2, length2)
      if carry == 1 {
        let new_result = ListNode(carry)
        new_result.next = result
        return new_result
      } else {
        return result
      }
    }
  }
  static func main() {
    let s = Solution()
    let a = ListNode(7)
    let b = ListNode(2)
    let c = ListNode(4)
    let d = ListNode(3)
    let e = ListNode(5)
    let f = ListNode(6)
    let g = ListNode(4)
    a.next = b
    b.next = c
    c.next = d
    e.next = f
    f.next = g
    var result = s.addTwoNumbers(a, e)
    while result != nil {
      print(result!.val)
      result = result!.next
    }
  }
}
