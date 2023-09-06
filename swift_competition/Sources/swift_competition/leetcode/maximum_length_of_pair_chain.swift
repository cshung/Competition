enum maximum_length_of_pair_chain {}

extension maximum_length_of_pair_chain {
  class Solution {
    func findLongestChain(_ pairs: [[Int]]) -> Int {
      var sorted = pairs
      sorted.sort { $0[1] < $1[1] }
      var current: [Int]? = nil
      var count = 0
      for pair in sorted {
        if current == nil {
          count = count + 1
          current = pair
        } else if pair[0] > current![1] {
          count = count + 1
          current = pair
        }
      }
      return count
    }
  }
  static func main() {
    print(Solution().findLongestChain([[1, 2], [2, 3], [3, 4]]))
  }
}
