enum length_of_the_longest_valid_substring {}

extension length_of_the_longest_valid_substring {
  class Solution {
    class LinkedListNode<T> {
      var value: T
      var next: LinkedListNode<T>?

      init(_ value: T) {
        self.value = value
      }
    }

    struct LinkedList<T> {
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
    class TrieNode {
      var children = [Character: TrieNode]()
      var failure: TrieNode?
      var pattern: String?
      var output: TrieNode?

      func add(_ s: String) {
        __add(Array(s), 0, s)
      }

      private func __add(_ s: [Character], _ i: Int, _ t: String) {
        if i < s.count {
          let first = s[i]
          if children[first] == nil {
            children[first] = TrieNode()
          }
          children[first]!.__add(s, i + 1, t)
        } else {
          pattern = t
        }
      }
    }

    func aho_corasick_bfs(_ root: TrieNode) {
      var queue = LinkedList<(TrieNode?, Character, TrieNode)>()
      queue.append((nil, " ", root))
      while !queue.isEmpty {
        let (p, c, v) = queue.removeFirst()!
        var tmp = p
        while let parent = tmp {
          if parent === root {
            break
          }
          if let child = parent.failure?.children[c] {
            v.failure = child
            if v.failure?.pattern != nil {
              v.output = v.failure
            } else if v.failure?.output != nil {
              v.output = v.failure?.output
            }
            break
          }
          tmp = parent.failure
        }
        if v.failure == nil {
          v.failure = root
        }
        for (child_key, child) in v.children {
          queue.append((v, child_key, child))
        }
      }
    }

    func aho_corasick(_ text: String, _ patterns: [String]) -> [(Int, String)] {
      let root = TrieNode()
      let text = Array(text)
      for pattern in patterns {
        root.add(pattern)
      }
      aho_corasick_bfs(root)
      var result = [(Int, String)]()
      var cursor = root
      var i = 0
      while i < text.count {
        let c = text[i]
        if let child = cursor.children[c] {
          cursor = child
          i += 1
          if cursor.pattern != nil {
            result.append((i - cursor.pattern!.count, cursor.pattern!))
          }
          var output_cursor = cursor.output
          while let output = output_cursor {
            result.append((i - output.pattern!.count, output.pattern!))
            output_cursor = output.output
          }
        } else {
          if cursor === root {
            i += 1
          } else {
            cursor = cursor.failure!
          }
        }
      }
      return result
    }

    func longestValidSubstring(_ word: String, _ forbidden: [String]) -> Int {
      var seen = [Character: Bool]()
      for c in word {
        seen[c] = true
      }
      var filtered = [String]()
      for f in forbidden {
        var skip = false
        for fc in f {
          if seen[fc] == nil {
            skip = true
            break
          }
        }
        if !skip {
          filtered.append(f)
        }
      }
      let matches = aho_corasick(word, filtered)
      var least_possible_start = 0
      var valid = [Int?](repeating: nil, count: word.count)
      for (start, s) in matches {
        least_possible_start = max(start + 1, least_possible_start)
        let end = start + s.count - 1
        valid[end] = least_possible_start
      }
      var current: Int
      if valid[0] == nil {
        current = 1
      } else {
        current = 0
      }
      var best = current
      for i in 1..<word.count {
        if valid[i] == nil {
          current += 1
        } else {
          current = i - valid[i]! + 1
        }
        if current > best {
          best = current
        }
      }
      return best
    }
  }
  static func main() {
    print(Solution().longestValidSubstring("cbaaaabc", ["aaa", "cb"]))
  }
}
