enum longest_alternating_subarray {}

extension longest_alternating_subarray {
  class Solution {
    func alternatingSubarray(_ nums: [Int]) -> Int {
      var length = 1
      var best = 1
      for i in 1..<nums.count {
        if nums[i] == nums[i - 1] + 1 {
          if length % 2 == 1 {
            length += 1
          } else {
            length = 2
          }
        } else if nums[i] == nums[i - 1] - 1 && length % 2 == 0 {
          length += 1
        } else {
          length = 1
        }
        best = max(best, length)
      }
      if best > 1 {
        return best
      } else {
        return -1
      }
    }
  }
  static func main() {
    print(Solution().alternatingSubarray([2, 3, 4, 3, 4]))
  }
}
