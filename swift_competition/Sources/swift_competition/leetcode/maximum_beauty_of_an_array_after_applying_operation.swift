enum maximum_beauty_of_an_array_after_applying_operation {}

extension maximum_beauty_of_an_array_after_applying_operation {
  class Solution {
    func maximumBeauty(_ nums: [Int], _ k: Int) -> Int {
      var intervals: [(Int, Int)] = []
      for n in nums {
        intervals.append((n - k, -1))
        intervals.append((n + k, +1))
      }
      intervals.sort { (a, b) -> Bool in
        if a.0 < b.0 {
          return true
        } else if a.0 == b.0 {
          return a.1 < b.1
        }
        return false
      }
      var best = 0
      var c = 0
      for (_, s) in intervals {
        c -= s
        if c > best {
          best = c
        }
      }
      return best
    }
  }
  static func main() {
    print(Solution().maximumBeauty([4, 6, 1, 2], 2))
  }
}
