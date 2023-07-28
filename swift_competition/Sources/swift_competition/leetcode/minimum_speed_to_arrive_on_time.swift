import Foundation;

enum minimum_speed_to_arrive_on_time {}

extension minimum_speed_to_arrive_on_time {
  class Solution {
    func feasible(dist: [Int], speed: Int, hour: Double) -> Bool {
      var time = 0.0
      for d in dist {
        time = ceil(time)
        let t = Double(d) / Double(speed)
        time += t
      }
      return time <= hour
    }

    func minSpeedOnTime(_ dist: [Int], _ hour: Double) -> Int {
      if feasible(dist: dist, speed: 1, hour: hour) {
        return 1
      } else if !feasible(dist: dist, speed: 10_000_000, hour: hour) {
        return -1
      } else {
        var lo = 1
        var hi = 10_000_000
        while true {
          if hi - lo == 1 {
            return hi
          }
          let mid = lo + (hi - lo) / 2
          if feasible(dist: dist, speed: mid, hour: hour) {
            hi = mid
          } else {
            lo = mid
          }
        }
      }
    }
  }
  static func main() {
    print(Solution().minSpeedOnTime([1, 3, 2], 6))
  }
}
