enum put_marbles_in_bags {}

extension put_marbles_in_bags {
  class Solution {
    func putMarbles(_ weights: [Int], _ k: Int) -> Int {
      let n = weights.count
      var pairs: [Int] = []
      for i in 0..<(n - 1) {
        pairs.append(weights[i] + weights[i + 1])
      }
      pairs.sort()
      var answer = 0
      for i in 0..<(k - 1) {
        answer = answer + pairs[n - 2 - i]
        answer = answer - pairs[i]
      }
      return answer
    }
  }

  static func main() {
    let s = Solution()
    print(s.putMarbles([1, 3, 5, 1], 2))
  }
}
