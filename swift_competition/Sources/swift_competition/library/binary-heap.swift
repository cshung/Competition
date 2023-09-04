extension library {
  class BinaryHeap<T: Comparable> {
    var items: [T?]
    var size: Int
    init(_ capacity: Int) {
      items = [T?](repeating: nil, count: capacity)
      size = 0
    }
    func push(_ value: T) {
      items[size] = value
      bubble_up(size)
      size = size + 1
    }
    func pop() -> T {
      let answer = items[0]!
      items[0] = items[size - 1]
      items[size - 1] = nil
      size = size - 1
      stone_down(0)
      return answer
    }
    func count() -> Int {
        return size
    }
    private func stone_down(_ parent: Int) {
      var parent = parent
      while true {
        let right = (parent + 1) * 2
        let left = right - 1
        if left >= size {
          return
        }
        var child = 10086
        if right >= size {
          child = left
        } else {
          if items[left]! > items[right]! {
            child = right
          } else {
            child = left
          }
        }
        if items[parent]! > items[child]! {
          let temp = items[parent]
          items[parent] = items[child]
          items[child] = temp
          parent = child
        } else {
          return
        }
      }
    }
    private func bubble_up(_ child: Int) {
      var child = child
      while true {
        if child == 0 {
          return
        }
        let parent = (child + 1) / 2 - 1
        if items[parent]! > items[child]! {
          let temp = items[parent]
          items[parent] = items[child]
          items[child] = temp
          child = parent
        } else {
          return
        }
      }
    }
  }
}
