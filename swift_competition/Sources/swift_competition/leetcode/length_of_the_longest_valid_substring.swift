enum length_of_the_longest_valid_substring {}

extension length_of_the_longest_valid_substring {
  class Solution {
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
      let matches = library.AhoCorasick().aho_corasick(word, filtered)
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
