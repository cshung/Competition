extension library {
  struct Deque<T> {
    class LinkedListNode<T> {
      var value: T
      var next: LinkedListNode<T>?

      init(_ value: T) {
        self.value = value
      }
    }
    var head: LinkedListNode<T>?
    var tail: LinkedListNode<T>?

    mutating func append(_ value: T) {
      let newNode = LinkedListNode(value)
      if let tailNode = tail {
        tailNode.next = newNode
      } else {
        head = newNode
      }
      tail = newNode
    }

    mutating func removeFirst() -> T? {
      guard let headNode = head else {
        return nil
      }
      head = headNode.next
      if head == nil {
        tail = nil
      }
      return headNode.value
    }

    var isEmpty: Bool {
      return head == nil
    }
  }
}
