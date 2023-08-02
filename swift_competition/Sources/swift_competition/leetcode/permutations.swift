import Foundation

enum permutations {}

extension permutations {
  class Solution {
    func permuteHelper(
      _ choices: library.Deque<Int>, _ digit: Int, _ buffer: inout [Int], _ answer: inout [[Int]]
    ) {
      if digit == buffer.count {
        answer.append(buffer)
      } else {
        var node = choices.head.next!
        while node !== choices.tail {
          buffer[digit] = node.value!
          let nodePrevWas = node.prev!
          let nodeNextWas = node.next!
          nodePrevWas.next = nodeNextWas
          nodeNextWas.prev = nodePrevWas
          permuteHelper(choices, digit + 1, &buffer, &answer)
          nodePrevWas.next = node
          nodeNextWas.prev = node
          node = node.next!
        }

      }
    }
    func permute(_ nums: [Int]) -> [[Int]] {
      var answer: [[Int]] = []
      var buffer = [Int](repeating: 0, count: nums.count)
      var choices = library.Deque<Int>()
      for n in nums {
        _ = choices.append(n)
      }
      permuteHelper(choices, 0, &buffer, &answer)
      return answer
    }
  }
  static func main() {
    print(Solution().permute([1, 2, 3]))
  }
}
