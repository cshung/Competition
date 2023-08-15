enum search_in_rotated_sorted_array_ii {}

extension search_in_rotated_sorted_array_ii {
  class Solution {
    func search(_ nums: [Int], _ target: Int) -> Bool {
      var lo = 0
      var hi = nums.count
      if nums[lo] == nums[hi - 1] {
        return nums.contains(target)
      }
      while true {
        if hi - lo == 1 {
          if nums[lo] == target {
            return true
          } else {
            return false
          }
        }
        if hi - lo == 2 {
          if nums[lo] == target {
            return true
          } else if nums[lo + 1] == target {
            return true
          } else {
            return false
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
          if rightSorted {
            return false
          } else {
            lo = mid
          }
        } else if rightSorted {
          hi = mid
        } else {
          assert(false)
        }
      }
    }
  }
  static func main() {
    print(Solution().search([2,5,6,0,0,1,2],0))
  }
}
