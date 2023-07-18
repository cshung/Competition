enum lru_cache {}

extension lru_cache {
  class LRUCache {
    var queue: library.Deque<(Int, Int)>
    var map: [Int: library.DequeNode<(Int, Int)>]
    let cap: Int
    var size: Int

    init(_ capacity: Int) {
      queue = library.Deque<(Int, Int)>()
      map = [:]
      cap = capacity
      size = 0
    }

    func get(_ key: Int) -> Int {
      let node = map[key]
      if let node = node {
        node.remove()
        let (key, value) = node.value!
        map[key] = queue.append((key, value))
        return value
      } else {
        return -1
      }
    }

    func put(_ key: Int, _ value: Int) {
      let node = map[key]
      if let node = node {
        node.remove()
        size = size - 1
      }
      if size == cap {
        let (key, _) = queue.removeFirst()!
        map.removeValue(forKey: key)
        size = size - 1
      }
      map[key] = queue.append((key, value))
      size = size + 1
    }
  }

  static func main() {
    let cache = LRUCache(2)
    cache.put(1, 1)
    cache.put(2, 2)
    print(cache.get(1))
    cache.put(3, 3)
    print(cache.get(2))
    cache.put(4, 4)
    print(cache.get(1))
    print(cache.get(3))
    print(cache.get(4))
  }
}
