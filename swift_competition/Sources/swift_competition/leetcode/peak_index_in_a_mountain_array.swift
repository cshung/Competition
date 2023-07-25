enum peak_index_in_a_mountain_array {}

extension peak_index_in_a_mountain_array {
  class Solution {
    func peakIndexInMountainArray(_ arr: [Int]) -> Int {
      let n = arr.count
      var lo = 0
      var hi = n - 2
      while true {
        if hi - lo == 1 {
          return hi
        }
        let mid = lo + (hi - lo) / 2
        if arr[mid] < arr[mid + 1] {
          lo = mid
        } else {
          hi = mid
        }
      }
    }
  }
  static func main() {
    print(Solution().peakIndexInMountainArray([0, 1, 0]))
  }
}
