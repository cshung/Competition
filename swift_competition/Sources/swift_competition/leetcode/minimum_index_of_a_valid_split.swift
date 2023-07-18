enum minimum_index_of_a_valid_split {}

extension minimum_index_of_a_valid_split {

  class Solution {
    func minimumIndex(_ nums: [Int]) -> Int {
      var count = 0
      var maj: Int?
      for n in nums {
        if count == 0 {
          maj = n
          count = 1
        } else if n == maj {
          count += 1
        } else {
          count -= 1
        }
      }
      var freq = 0
      for n in nums {
        if n == maj {
          freq += 1
        }
      }
      var left = 0
      for (i, n) in nums.enumerated() {
        if n == maj {
          left += 1
        }
        let right = freq - left
        let left_length = i + 1
        let right_length = nums.count - left_length
        if left * 2 > left_length && right * 2 > right_length {
          return i
        }
      }
      return -1
    }
  }
  static func main() {
    print(Solution().minimumIndex([1, 2, 2, 2]))
  }
}
