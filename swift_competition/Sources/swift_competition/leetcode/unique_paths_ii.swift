enum unique_paths_ii {}

extension unique_paths_ii {
  class Solution {
    func uniquePathsWithObstacles(_ obstacleGrid: [[Int]]) -> Int {
      let m = obstacleGrid.count
      let n = obstacleGrid[0].count
      var dp = Array(repeating: Array(repeating: 0, count: n), count: m)

      for r in 0..<m {
        for c in 0..<n {
          if r == 0 && c == 0 {
            if obstacleGrid[r][c] == 1 {
              dp[r][c] = 0
            } else {
              dp[r][c] = 1
            }
          } else if obstacleGrid[r][c] == 1 {
            dp[r][c] = 0
          } else {
            var p = 0
            if r > 0 {
              p += dp[r - 1][c]
            }
            if c > 0 {
              p += dp[r][c - 1]
            }
            dp[r][c] = p
          }
        }
      }

      return dp[m - 1][n - 1]
    }
  }
  static func main() {
    print(Solution().uniquePathsWithObstacles([[0,0,0],[0,1,0],[0,0,0]]))
  }
}
