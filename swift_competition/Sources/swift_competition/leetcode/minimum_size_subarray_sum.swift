enum minimum_size_subarray_sum {}

extension minimum_size_subarray_sum {
  class Solution {
    func minSubArrayLen(_ target: Int, _ nums: [Int]) -> Int {
      var sum = 0
      var sums = [0]
      for i in 0..<nums.count {
        let n = nums[i]
        sum = sum + n
        sums.append(sum)
      }
      var s = 0
      var answer = 0
      for e in 1..<nums.count+1 {
        if sums[e] - sums[s] >= target {
          while true {
            if sums[e] - sums[s + 1] >= target {
              s = s + 1
            } else {
              break
            }
          }
          if answer == 0 || answer > e - s {
            answer = e - s 
          } 
        }
      }
      return answer
    }
  }

  static func main() {
    let s = Solution()
    print(s.minSubArrayLen(7, [2, 3, 1, 2, 4, 3]))
  }
}
