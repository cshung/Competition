import Foundation

enum predict_the_winner {}

extension predict_the_winner {
  class Solution {
    func PredictTheWinner(_ nums: [Int]) -> Bool {
      var diff = nums
      let n = nums.count
        for l in 2..<n+1 {
          var next = [Int]()
          for i in 0...(n - l) {
            let j = i + l - 1
            let head = nums[i] - diff[i + 1]
            let tail = nums[j] - diff[i]
            let best = max(head, tail)
            next.append(best)
          }
          diff = next
      }
      return diff[0] >= 0
    }
  }
  static func main() {
    print(Solution().PredictTheWinner([0]))
  }
}
