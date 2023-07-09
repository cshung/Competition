enum substring_with_largest_variance {}

extension substring_with_largest_variance {
  class Solution {
    func largestVariance(_ s: String) -> Int {
      var best = 0
      let str = Array(s)
      let a = Array("a")[0].asciiValue!
      for b in 0..<26 {
        for s in 0..<26 {
          if b == s {
            continue
          }
          var has_b = false
          var has_s = false
          var start_s = false
          var leading_b_count = 0
          var sum = 0
          for i in 0..<str.count {
            let e = str[i].asciiValue! - a
            if has_b {
              if has_s {
                if e == b {
                  // has s, has b, seeing b
                  sum = sum + 1
                  if sum > best {
                    best = sum
                  }
                } else if e == s {
                  // has s, has b, seeing s
                  if start_s {
                    start_s = false
                  } else {
                    sum = sum - 1
                  }
                  if sum < 0 {
                    start_s = true
                    has_b = false
                    leading_b_count = 0
                    sum = 0
                  }
                }
              } else {
                if e == b {
                  // no s, has b, seeing b
                  leading_b_count += 1
                } else if e == s {
                  // no s, has b, seeing s
                  sum = leading_b_count - 1
                  if sum > best {
                    best = sum
                  }
                  has_s = true
                }
              }
            } else {
              if has_s {
                if e == b {
                  // has s, no b, seeing b
                  has_b = true
                  start_s = true
                } else if e == s {
                  // has s, no b, seeing s
                }
              } else {
                if e == b {
                  // no b, no s, seeing b
                  has_b = true
                  leading_b_count = 1
                } else if e == s {
                  // no b, no s, seeing s
                  has_s = true
                }

              }
            }
          }
        }
      }
      return best
    }
  }

  static func main() {
    let s = Solution()
    print(s.largestVariance("aabbb"))
  }
}
