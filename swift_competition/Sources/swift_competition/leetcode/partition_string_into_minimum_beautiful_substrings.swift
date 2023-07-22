enum partition_string_into_minimum_beautiful_substrings {}

extension partition_string_into_minimum_beautiful_substrings {
  class Solution {
    func minimumBeautifulSubstrings(_ s: String) -> Int {
      var patterns = [String]()
      var n = 1
      while true {
        let b = String(n, radix: 2)
        if b.count > s.count {
          break
        }
        patterns.append(b)
        n *= 5
      }
      let aho_corasick_result = library.AhoCorasick().aho_corasick(s, patterns)
      var adj = [Int: [Int]]()
      for match in aho_corasick_result {
        let src = match.0
        let dst = match.0 + match.1.count
        if adj[src] == nil {
          adj[src] = [Int]()
        }
        adj[src]?.append(dst)
      }
      var queue = library.Deque<(Int, Int)>()
      _ = queue.append((0, 0))
      var visited = Set<Int>()
      while !queue.isEmpty {
        let (src, cost) = queue.removeFirst()!
        if visited.contains(src) {
          continue
        }
        visited.insert(src)
        if src == s.count {
          return cost
        }
        if let nextNodes = adj[src] {
          for dst in nextNodes {
            _ = queue.append((dst, cost + 1))
          }
        }
      }
      return -1
    }
  }
  static func main() {
    print(Solution().minimumBeautifulSubstrings("1011"))
  }
}
