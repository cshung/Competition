import Foundation

enum minimize_the_maximum_difference_of_pairs {}

extension minimize_the_maximum_difference_of_pairs {
  class Solution {
    func minimizeMax(_ nums: [Int], _ p: Int) -> Int {
      if p == 0 {
        return 0
      }
      var nums = nums
      let n = nums.count
      nums.sort()
      var hi = nums[n - 1] - nums[0]
      var lo = -1
      while true {
        if hi - lo == 1 {
          return hi
        }
        let mid = lo + (hi - lo) / 2
        var i = 0
        var t = 0
        while true {
          if nums[i + 1] - nums[i] <= mid {
            t += 1
            i += 2
          } else {
            i += 1
          }
          if i >= n - 1 {
            break
          }
          if t == p {
            break
          }
        }
        if t == p {
          hi = mid
        } else {
          lo = mid
        }
      }
    }
  }
  static func main() {
    print(Solution().minimizeMax([10, 1, 2, 7, 1, 3], 2))
  }
}
