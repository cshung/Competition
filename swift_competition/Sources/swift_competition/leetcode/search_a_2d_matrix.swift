enum search_a_2d_matrix {}

extension search_a_2d_matrix {
  class Solution {
    func searchMatrix(_ matrix: [[Int]], _ target: Int) -> Bool {
      let m = matrix.count
      let n = matrix[0].count

      if target < matrix[0][0] {
        return false
      } else if target == matrix[0][0] {
        return true
      }

      if target > matrix[m - 1][n - 1] {
        return false
      } else if target == matrix[m - 1][n - 1] {
        return true
      }

      var lo = 0
      var hi = m * n - 1

      while true {
        if hi - lo <= 1 {
          return false
        }

        let mid = lo + (hi - lo) / 2
        let c = mid % n
        let r = (mid - c) / n

        if matrix[r][c] == target {
          return true
        } else if matrix[r][c] > target {
          hi = mid
        } else {
          lo = mid
        }
      }
    }
  }
  static func main() {
    print(Solution().searchMatrix([[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]], 3))
  }
}
