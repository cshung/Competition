enum word_break {}

extension word_break {

  class Solution {
    func wordBreak(_ s: String, _ wordDict: [String]) -> Bool {
      let root = library.TrieNode()
      for word in wordDict {
        root.add(word)
      }
      let str = Array(s)
      let n = str.count
      var reachable = Array(repeating: false, count: n + 1)
      reachable[0] = true
      for i in 0..<n {
        if reachable[i] {
          var j = i
          var cur = root
          while j < n {
            let c = str[j]
            let next = cur.children[c]
            if next == nil {
              break
            } else {
              cur = next!
              j = j + 1
              if cur.pattern != nil {
                reachable[j] = true
              }
            }
          }
        }
      }
      return reachable[n]
    }
  }
  static func main() {
    print(Solution().wordBreak("leetcode", ["leet", "code"]))
  }
}
