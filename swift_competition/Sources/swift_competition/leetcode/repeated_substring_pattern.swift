enum repeated_substring_pattern {}

extension repeated_substring_pattern {
  class Solution {
    func repeatedSubstringPattern(_ s: String) -> Bool {
      let n = s.count
      let h = n / 2 + 1
      var z = [Int](repeating: 0, count: h)
      var rightmostZBoxLeft = 0
      var rightmostZBoxRight = 0
      let s = Array(s)

      for i in 1..<h {
        if i < rightmostZBoxRight {
          let length = min(z[i - rightmostZBoxLeft], rightmostZBoxRight - i)
          z[i] = length
        }

        while i + z[i] < s.count && s[i + z[i]] == s[z[i]] {
          z[i] += 1
        }

        if i + z[i] > rightmostZBoxRight {
          rightmostZBoxLeft = i
          rightmostZBoxRight = i + z[i]
        }
        if (i + z[i] == n) && (n % i == 0) {
          return true
        }
      }
      return false
    }
  }
  static func main() {
    print(Solution().repeatedSubstringPattern("abab"))
  }
}
