import Foundation

enum maximum_running_time_of_n_computers {}

extension maximum_running_time_of_n_computers {
  class Solution {
    func maxRunTime(_ n: Int, _ batteries: [Int]) -> Int {
      var sum = 0
      for b in batteries {
        sum += b
      }
      var right = sum / n + 1
      var left = 0

      while true {
        if left == right - 1 {
          return left
        }

        let mid = (left + right) / 2

        var total = 0
        for b in batteries {
          total += min(b, mid)
        }

        if total >= n * mid {
          left = mid
        } else {
          right = mid
        }
      }
    }
  }
  static func main() {
    print(Solution().maxRunTime(2, [3, 3, 3]))
  }
}
