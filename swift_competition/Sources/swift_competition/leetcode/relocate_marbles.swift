enum relocate_marbles {}

extension relocate_marbles {
  class Solution {
    func relocateMarbles(_ nums: [Int], _ moveFrom: [Int], _ moveTo: [Int]) -> [Int] {
      var map = [Int: Bool]()
      for i in nums {
        map[i] = true
      }
      for i in 0..<moveFrom.count {
        map.removeValue(forKey: moveFrom[i])
        map[moveTo[i]] = true
      }
      return map.keys.sorted()
    }
  }
  static func main() {
    print(Solution().relocateMarbles([1, 6, 7, 8], [1, 7, 2], [2, 9, 5]))
  }
}
