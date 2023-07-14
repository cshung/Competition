enum longest_arithmetic_subsequence_of_given_difference {}

extension longest_arithmetic_subsequence_of_given_difference {
  class Solution {
    func longestSubsequence(_ arr: [Int], _ difference: Int) -> Int {
      var map = [Int: Int]()
      var best = 0
      for n in arr {
        let prev = n - difference
        let last = map[prev]
        if let last = last {
          map[n] = last + 1
        } else {
          map[n] = 1
        }
        if best < map[n]! {
          best = map[n]!
        }
      }
      return best
    }
  }
  static func main() {
    let s = Solution()
    print(s.longestSubsequence([1, 2, 3, 4], 1))
  }
}
