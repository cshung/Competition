import Foundation

enum search_in_rotated_sorted_array {}

extension search_in_rotated_sorted_array {
  class Solution {
    func search(_ nums: [Int], _ target: Int) -> Int {
      var lo = 0
      var hi = nums.count
      while true {
        if hi - lo == 1 {
          if nums[lo] == target {
            return lo
          } else {
            return -1
          }
        }
        if hi - lo == 2 {
          if nums[lo] == target {
            return lo
          } else if nums[lo + 1] == target {
            return lo + 1
          } else {
            return -1
          }
        }
        let mid = lo + (hi - lo) / 2
        let leftSorted = nums[mid - 1] >= nums[lo]
        let rightSorted = nums[hi - 1] >= nums[mid]
        if leftSorted && nums[lo] <= target && target <= nums[mid - 1] {
          hi = mid
        } else if rightSorted && nums[mid] <= target && target <= nums[hi - 1] {
          lo = mid
        } else if leftSorted {
          lo = mid
        } else {
          hi = mid
        }
      }
    }
  }
  static func main() {
    print(Solution().search([4, 5, 6, 7, 0, 1, 2], 0))
  }
}
