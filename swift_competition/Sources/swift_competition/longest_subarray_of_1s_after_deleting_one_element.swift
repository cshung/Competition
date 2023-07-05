enum longest_subarray_of_1s_after_deleting_one_element {}

extension longest_subarray_of_1s_after_deleting_one_element {
  class Solution {
    func longestSubarray(_ nums: [Int]) -> Int {
      var n = nums[0]
      var d = 1
      var best = 1
      for i in 1..<nums.count {
        let v = nums[i]
        var new_n = 0
        var new_d = 0
        if v == 0 {
          new_d = n + 1
        } else {
          new_n = n + 1
          if n > d {
            new_d = n + 1
          } else {
            new_d = d + 1
          }
        }
        n = new_n
        d = new_d
        if d > best {
          best = d
        }
      }
      return best - 1
    }
  }

  static func main() {
    let s = Solution()
    print(s.longestSubarray([1, 1, 0, 1]))
  }
}
