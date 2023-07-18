extension library {
  class DequeNode<T> {
    var value: T?
    var next: DequeNode<T>?
    weak var prev: DequeNode<T>?

    func remove() {
      prev!.next = next
      next!.prev = prev
    }
  }
  struct Deque<T> {
    var head: DequeNode<T>
    var tail: DequeNode<T>

    init() {
      head = DequeNode()
      tail = DequeNode()
      head.next = tail
      tail.prev = head
    }

    mutating func append(_ value: T) -> DequeNode<T> {
      let newNode = DequeNode<T>()
      newNode.value = value
      newNode.prev = tail.prev
      newNode.next = tail
      newNode.prev!.next = newNode
      newNode.next!.prev = newNode
      return newNode
    }

    mutating func removeFirst() -> T? {
      let victim = head.next!
      victim.remove()
      return victim.value!
    }

    var isEmpty: Bool {
      return head.next! === tail
    }
  }
}
