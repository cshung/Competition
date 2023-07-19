enum non_overlapping_intervals {}

extension non_overlapping_intervals {

  class Solution {
    func eraseOverlapIntervals(_ intervals: [[Int]]) -> Int {
      var intervals = intervals
      intervals.sort(by: { (a: [Int], b: [Int]) -> Bool in
        return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0])
      })
      var end = -50001
      var count = 0
      for interval in intervals {
        if interval[0] < end {
          count = count + 1
        } else {
          end = interval[1]
        }
      }
      return count
    }
  }
  static func main() {
    print(Solution().eraseOverlapIntervals([[1, 2], [2, 3], [3, 4], [1, 3]]))
  }
}
