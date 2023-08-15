enum check_if_there_is_a_valid_partition_for_the_array {}

extension check_if_there_is_a_valid_partition_for_the_array {
  class Solution {
    func validPartition(_ nums: [Int]) -> Bool {
      let n = nums.count
      var dp = [Bool](repeating: false, count: 4)
      dp[0] = true
      var head = 2

      for i in (0..<(n - 1)).reversed() {
        var possible = false

        if nums[i] == nums[i + 1] {
          possible = dp[(head - 2 + 4) % 4]
        }

        if !possible {
          if i < n - 2 && dp[(head - 3 + 4) % 4] {
            let a = nums[i]
            let b = nums[i + 1]
            let c = nums[i + 2]

            if a == b && b == c {
              possible = true
            } else if b == (a + 1) && c == (b + 1) {
              possible = true
            }
          }
        }

        dp[head] = possible
        head = (head + 1) % 4
      }

      return dp[(head - 1 + 4) % 4]
    }
  }
  static func main() {
    print(Solution().validPartition([4,4,4,5,6]))
  }
}
