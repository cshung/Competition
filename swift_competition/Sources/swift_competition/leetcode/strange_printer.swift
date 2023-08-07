import Foundation

enum strange_printer {}

extension strange_printer {
  class Solution {
    func strangePrinter(_ s: String) -> Int {
      let str = Array(s)
      let n = s.count
      var dp = [[Int]](repeating: [Int](repeating: 0, count: n), count: n)

      for length in 2...n {
        for l in 0...(n - length) {
          let r = l + length - 1
          var i = l
          while str[i] == str[r] && i < r {
            i += 1
          }
          if i == r {
            dp[l][r] = 0
          } else {
            dp[l][r] = 1 + dp[i + 1][r]

            for e in (i + 1)..<r {
              dp[l][r] = min(dp[l][r], 1 + dp[i][e] + dp[e + 1][r])
            }
          }
        }
      }

      return 1 + dp[0][n - 1]
    }
  }
  static func main() {
    print(Solution().strangePrinter("aaabbb"))
  }
}
