enum knight_probability_in_chessboard {}

extension knight_probability_in_chessboard {

  class Solution {
    func knightProbability(_ n: Int, _ k: Int, _ row: Int, _ column: Int) -> Double {
      var pre = Array(repeating: Array(repeating: 0.0, count: n), count: n)
      var post = Array(repeating: Array(repeating: 0.0, count: n), count: n)
      pre[row][column] = 1.0
      let dr = [-2, -1, 1, 2, 2, 1, -1, -2]
      let dc = [1, 2, 2, 1, -1, -2, -2, -1]
      for _ in 0..<k {
        for r in 0..<n {
          for c in 0..<n {
            if pre[r][c] != 0 {
              for m in 0..<8 {
                let nr = r + dr[m]
                let nc = c + dc[m]
                if 0 <= nr && nr < n && 0 <= nc && nc < n {
                  post[nr][nc] += pre[r][c] / 8.0
                }
              }
            }
          }
        }
        let temp = pre
        pre = post
        post = temp
        for r in 0..<n {
          for c in 0..<n {
            post[r][c] = 0.0
          }
        }
      }
      var answer = 0.0
      for r in 0..<n {
        for c in 0..<n {
          answer += pre[r][c]
        }
      }
      return answer
    }
  }
  static func main() {
    print(Solution().knightProbability(3, 2, 0, 0))
  }
}
