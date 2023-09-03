enum combinations {}

extension combinations {
  class Solution {
    func combineHelper(
      _ choices: library.Deque<Int>, _ digit: Int, _ buffer: inout [Int], _ answer: inout [[Int]]
    ) {
      if digit == buffer.count {
        answer.append(buffer)
      } else {
        let head = choices.head
        var node = choices.head.next!
        while node !== choices.tail {
          buffer[digit] = node.value!
          let headNextWas = head.next!
          let nodePrevWas = node.prev!
          node.prev = head
          head.next = node.next!
          combineHelper(choices, digit + 1, &buffer, &answer)
          head.next = headNextWas
          node.prev = nodePrevWas
          node = node.next!
        }

      }
    }
    func combine(_ n: Int, _ k: Int) -> [[Int]] {
      var answer: [[Int]] = []
      var buffer = [Int](repeating: 0, count: k)
      var choices = library.Deque<Int>()
      for i in 0..<n {
        _ = choices.append(i + 1)
      }
      combineHelper(choices, 0, &buffer, &answer)
      return answer
    }
  }
  static func main() {
    print(Solution().combine(4, 2))
  }
}
