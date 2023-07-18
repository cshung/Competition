enum single_number_ii {}

extension single_number_ii {
  class Solution {
    func singleNumber(_ nums: [Int]) -> Int {
      var ans: [Int] = []
      var s = 0
      for x in nums {
        var n = x
        var digits: [Int] = []
        if n < 0 {
          n = -n
          s = s + 1
          s = s % 3
        }
        while n > 0 {
          digits.append(n % 3)
          n = n / 3
        }
        while ans.count < digits.count {
          ans.append(0)
        }
        for i in 0..<digits.count {
          ans[i] = (ans[i] + digits[i]) % 3
        }
      }
      var out = 0
      for i in ans.reversed() {
        out = out * 3
        out = out + i
      }
      return (1 - s * 2) * out
    }
  }

  static func main() {
    let s = Solution()
    print(s.singleNumber([2, 2, 3, 2]))
  }
}
