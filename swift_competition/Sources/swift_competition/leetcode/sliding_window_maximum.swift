enum sliding_window_maximum {}

extension sliding_window_maximum {
  class Solution {
    func maxSlidingWindow(_ nums: [Int], _ k: Int) -> [Int] {
      let n = nums.count
      var maxs = [Int](repeating: 0, count: k)
      var left = 0
      var right = k - 1
      var answers = [Int]()

      for i in k..<n + 1 {
        if left == 0 {
          maxs[0] = nums[i - 1]
          for j in 1..<k {
            maxs[j] = max(maxs[j - 1], nums[i - j - 1])
          }
          left = k
          right = k - 1
        }

        var best = maxs[left - 1]
        if right < k - 1 {
          best = max(best, maxs[right + 1])
        }

        answers.append(best)

        if i == n {
          break
        }

        left -= 1

        if right == k - 1 {
          maxs[k - 1] = nums[i]
        } else {
          maxs[right] = max(nums[i], maxs[right + 1])
        }

        right -= 1
      }

      return answers
    }
  }
  static func main() {
    print(Solution().maxSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3))
  }
}
