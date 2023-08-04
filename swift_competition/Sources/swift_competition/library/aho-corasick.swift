extension library {
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
  class AhoCorasick {
    func aho_corasick_bfs(_ root: TrieNode) {
      var queue = library.Deque<(TrieNode?, Character, TrieNode)>()
      _ = queue.append((nil, " ", root))
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
          _ = queue.append((v, child_key, child))
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
  }
}
