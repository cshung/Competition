enum interleaving_string {}

extension interleaving_string {
  class Solution {
    func isInterleaveHelper(
      _ a1: inout [Character], _ a2: inout [Character], _ a3: inout [Character]
    ) -> Bool {
      if a2.count > a1.count {
        return isInterleaveHelper(&a2, &a1, &a3)
      }
      var dp = [[Bool]](repeating: [Bool](repeating: false, count: a2.count + 1), count: 2)
      for r in 0...a1.count {
        for c in 0...a2.count {
          let curr = r % 2
          let prev = 1 - curr
          let last = r + c - 1
          if r == 0 && c == 0 {
            dp[curr][0] = true
          } else if r > 0 && dp[prev][c] && a1[r-1] == a3[last] {
            dp[curr][c] = true
          } else if c > 0 && dp[curr][c-1] && a2[c-1] == a3[last] {
            dp[curr][c] = true
          } else {
            dp[curr][c] = false
          }
        }
      }
      return dp[a1.count % 2][a2.count]
    }
    func isInterleave(_ s1: String, _ s2: String, _ s3: String) -> Bool {
      var a1 = Array(s1)
      var a2 = Array(s2)
      var a3 = Array(s3)
      if a1.count + a2.count != a3.count {
        return false
      }
      return isInterleaveHelper(&a1, &a2, &a3)
    }
  }

  static func main() {
    print(Solution().isInterleave("aabcc", "dbbca", "aadbbcbcac"))
  }
}
