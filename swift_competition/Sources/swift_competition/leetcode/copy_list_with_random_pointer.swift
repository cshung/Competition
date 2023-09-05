enum copy_list_with_random_pointer {}

extension copy_list_with_random_pointer {

  public class Node {
    public var val: Int
    public var next: Node?
    public var random: Node?
    public init(_ val: Int) {
      self.val = val
      self.next = nil
      self.random = nil
    }
  }

  class Solution {
    func copyRandomList(_ head: Node?) -> Node? {
      if head == nil {
        return nil
      }
      var current: [Node] = []
      var clone: [Node] = []
      var cur = head
      while cur != nil {
        let curr = cur!
        current.append(curr)
        clone.append(Node(curr.val))        
        cur = curr.next
        current[current.count - 1].next = clone[clone.count - 1]
      }
      let n = current.count
      for i in 0..<n {
        clone[i].random = current[i].random?.next
      }
      for i in 1..<n {
        current[i-1].next = current[i]
        clone[i-1].next = clone[i]
      }
      current[n-1].next = nil
      return clone[0]
    }
  }
  static func main() {
    let a = Node(7)
    let b = Node(11)
    let c = Node(13)
    let d = Node(10)
    let e = Node(1)
    a.next = b
    b.next = c
    c.next = d
    d.next = e
    a.random = nil
    b.random = a
    c.random = e
    d.random = c
    e.random = a
    let answer = Solution().copyRandomList(a)
    let _a = answer!;
    let _b = _a.next!;
    let _c = _b.next!;
    let _d = _c.next!;
    let _e = _d.next!;
    print(_a.val)
    print(_b.val)
    print(_c.val)
    print(_d.val)
    print(_e.val)
    print(_a.random === nil)
    print(_b.random === _a)
    print(_c.random === _e)
    print(_d.random === _c)
    print(_e.random === _a)
    print(a.next === b)
    print(b.next === c)
    print(c.next === d)
    print(d.next === e)
    print(e.next === nil)
    a.random = nil
    b.random = nil
    c.random = nil
    d.random = nil
    e.random = nil
    _a.random = nil
    _b.random = nil
    _c.random = nil
    _d.random = nil
    _e.random = nil
  }
}
