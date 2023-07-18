enum sum_of_squares_of_special_elements {}

extension sum_of_squares_of_special_elements {
  class Solution {
    func sumOfSquares(_ nums: [Int]) -> Int {
      let n = nums.count
      var s = 0
      for (i, v) in nums.enumerated() {
        if n % (i + 1) == 0 {
          s += v * v
        }
      }
      return s
    }
  }
  static func main() {
    print(Solution().sumOfSquares([1, 2, 3, 4]))
  }
}
